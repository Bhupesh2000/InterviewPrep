# Bugs Found in the Logging Framework — and How They Were Fixed

This file lists every bug that was reported in the first version of this framework,
in the same order (most serious first). For each one: what was wrong, why it was
wrong in plain language, and what the fix was.

---

## 1. Data race in the formatters — `std::ctime` (most serious)

**What was wrong**

Both formatters built the timestamp like this:

```cpp
std::string s = std::ctime(&t1);
```

`std::ctime` does not create a new string. It writes the text into **one buffer that
belongs to the whole program** and hands back a pointer to it. Every thread that
formats a message writes into that same buffer at the same time.

ThreadSanitizer caught it:

```
WARNING: ThreadSanitizer: data race
  Write of size 8 by thread T2:
    #0 ctime
    #1 PlainTextFormatter::format
    #2 ConsoleAppender::appendMessage
```

The per-appender mutex could never have prevented this. The design choice — one mutex
per appender, so that different destinations can log at the same time — is fine, but
it only works if the appenders never touch the same data. `ctime` is shared data
hiding inside an innocent-looking function call, so `ConsoleAppender` (holding its
mutex) and `FileAppender` (holding a *different* mutex) both wrote to that one buffer
at once.

**How it was fixed**

New file [TimeUtil.h](TimeUtil.h) with a helper that uses
`localtime_r`, which fills a `std::tm` that the *caller* owns, and `std::put_time` to
turn it into text:

```cpp
inline std::string formatTimestamp(std::chrono::system_clock::time_point tp){
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    std::tm tmBuf{};
    localtime_r(&t, &tmBuf);        // no shared buffer

    std::ostringstream out;
    out << std::put_time(&tmBuf, "%Y-%m-%d %H:%M:%S");
    return out.str();
}
```

Now nothing is shared, so formatting is safe from any number of threads. Both
formatters call this helper. Verified with a clean `-fsanitize=thread` run.

---

## 2. `FileAppender` was writing to the console

**What was wrong**

```cpp
// FileAppender
std::cout << "Writing to file :" << formatter->format(m);
```

It was a placeholder, but it broke the one rule the locking strategy depends on:
**each appender must own its own destination.** `ConsoleAppender` owns `std::cout` and
guards it with its own mutex; the stub `FileAppender` wrote to `std::cout` too, but
guarded by a *different* mutex. Two locks over one resource protect nothing, so
console and "file" output could interleave in the middle of a record.

**How it was fixed**

[FileAppender.h](appender/FileAppender.h) now owns a real
`std::ofstream` and writes to an actual file, so the two appenders really do have
separate destinations and the per-appender mutex is meaningful again:

```cpp
class FileAppender : public LogAppender{
    std::ofstream out;
public:
    FileAppender(Formatter* formatter, const std::string& fileName) :
        LogAppender(formatter), out(fileName, std::ios::app){ ... }
```

`main.cpp` passes `"app.log"`.

---

## 3. The output was malformed

**What was wrong**

The actual run looked like this:

```
[Debug] : Thread 1 : connecting to the databaseWriting to console :Sun Aug  9...
```

Two separate problems:

1. `std::ctime` puts a `\n` at the **end of the timestamp**, which landed in the
   *middle* of the record — and there was no newline at the end, so consecutive
   records ran into each other.
2. The XML formatter never closed its message tag: `"\n<message>\n"` should have been
   `</message>`.

**How it was fixed**

Each formatter now produces exactly one record ending in exactly one `\n`.

Plain text:

```cpp
return formatTimestamp(m.getTimeStamp())
     + " [" + getString(m.getLevel()) + "] : "
     + m.getMessageString() + "\n";
```

```
Writing to console : 2026-08-09 22:36:55 [Debug] : Thread 2 : connecting to the database
```

XML — one record per line, tags properly closed, and special characters
(`<`, `>`, `&`, quotes) escaped so a user message can't produce invalid XML:

```
<record><timestamp>2026-08-09 22:36:55</timestamp><level>Error</level><message>Thread 1 : failed to write to disk</message></record>
```

---

## 4a. Messages were copied everywhere (`const Message&`)

**What was wrong**

Every function on the logging path took its `Message` **by value**, meaning a fresh
copy of the message string each time:

```cpp
void handle(Message m);
void notifyAll(Message m);
void appendMessage(Message m);
std::string format(Message m);
std::string getMessageString() const;   // returns a copy too
```

That is roughly five string copies for a single log call, on the hot path, in a
framework whose whole selling point is being cheap.

**How it was fixed**

Everything on the path now takes `const Message&`, and `getMessageString()` returns
`const std::string&`:

```cpp
void handle(const Message& m);
void notifyAll(const Message& m);
virtual void appendMessage(const Message& m) = 0;
virtual std::string format(const Message& m) const = 0;
const std::string& getMessageString() const;
```

Zero copies of the message now — the one string that is built is the formatted output
itself.

---

## 4b. Deleting appenders that the singleton still points to

**What was wrong**

```cpp
delete console;
delete file;
return 0;
```

`Logger` is a function-local `static`, so it is destroyed **after** `main()` returns.
When `main()` deleted the appenders, the handlers were left holding pointers to freed
memory. Nothing crashed only because nothing logged after that point — a latent
use-after-free, not a safe program.

**How it was fixed**

`Logger` gained a `shutdown()` that unregisters the appenders while they are still
alive, and `main()` calls it before deleting anything:

```cpp
// Logger.h
void shutdown(){
    for(LogHandler* h = handler; h != nullptr; h = h -> getNext()){
        h -> clearAppenders();
    }
}
```

```cpp
// main.cpp — all threads have joined, single threaded again
logger.shutdown();
delete console;
delete file;
```

---

## 5. The handler chain leaked

**What was wrong**

`~LogHandler()` was written to delete the rest of the chain:

```cpp
virtual ~LogHandler(){ delete next; }
```

But `Logger` had **no destructor**, so `handler` (the head of the chain) was never
deleted — and a cascade that is never started never runs. All three handlers leaked.
The mechanism was built; the trigger was missing.

**How it was fixed**

`Logger` now has a destructor that deletes the head, which sets off the cascade:

```cpp
~Logger(){
    delete handler;
}
```

Verified with macOS `leaks`: **0 leaks for 0 total leaked bytes.**

---

## 6. A mutex that only one side locked

**What was wrong**

```cpp
void subscribe(LogAppender* appender){
    std::lock_guard<std::mutex> lock(mtx);   // writer locks
    ...
}
void notifyAll(Message m){
    for(auto it : observers){ ... }          // reader does NOT lock
}
```

A lock only works if **everyone** who touches the data takes it. Here the writer
locked and the reader didn't, so it bought no safety at all — it only cost a lock on
every registration.

**How it was fixed**

Appender registration is startup-only configuration: it happens on one thread, before
any worker thread starts. So the honest fix is to say so and remove the mutex rather
than pretend to lock:

```cpp
// Configuration-only state. subscribe()/clearAppenders() are documented as
// startup / shutdown operations, called from a single thread before the
// worker threads start and after they have joined. notifyAll() therefore
// only ever reads a vector nobody is writing.
std::vector<LogAppender*> observers;
```

(If registration at runtime were ever needed, the correct fix would be a
`shared_mutex` locked by *both* sides — not the half-lock that was there.)

---

## 7. `threshold` was a plain `int` read by many threads

**What was wrong**

```cpp
int threshold;
```

Every worker thread reads it on every log call, and `setThreshold()` writes it. In
this particular `main()` the writes happen between `join()` calls, so this run was
safe — but the public API openly invites a caller to change the threshold while
threads are logging, which is a data race.

**How it was fixed**

```cpp
std::atomic<int> threshold;
```

Now changing the threshold at any time is well defined.

---

## 8. `setThreshold(int)` threw away type safety

**What was wrong**

```cpp
void setThreshold(int i);
...
logger.setThreshold(getValue(MessageLevel::DEBUG));
```

The whole point of `enum class MessageLevel` is that a caller *cannot* pass a
meaningless value. Taking a raw `int` handed that protection straight back —
`setThreshold(42)` would compile.

**How it was fixed**

```cpp
void setThreshold(MessageLevel level){
    threshold = getValue(level);
}
```

```cpp
logger.setThreshold(MessageLevel::DEBUG);   // main.cpp
```

---

## Minor fixes

| Issue | Fix |
|---|---|
| `canHandle` / `format` were non-const | Both are `const` now, in the base classes and all overrides — they only read. |
| Single-argument constructors were implicit | `explicit` on `LogAppender` and `ConsoleAppender`, so a `Formatter*` cannot silently convert into an appender. |
| `notifyAll` was public | Moved to `protected` — only `handle()` should fan a message out. |

---

## How the fixes were verified

```bash
clang++ -std=c++17 -Wall -Wextra -fsanitize=thread -g -o main_tsan main.cpp && ./main_tsan
```

- No compiler warnings with `-Wall -Wextra`.
- ThreadSanitizer: clean, no races reported.
- macOS `leaks --atExit`: 0 leaks.
- Console output: one well-formed record per line.
- `app.log`: one valid, properly closed XML record per line.
