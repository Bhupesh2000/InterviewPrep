#ifndef LOGGER_H
#define LOGGER_H

#include <atomic>
#include <string>

#include "./Message.h"
#include "./MessageLevel.h"
#include "./logHandler/LogHandler.h"
#include "./logHandler/DebugLogHandler.h"
#include "./logHandler/InfoLogHandler.h"
#include "./logHandler/ErrorLogHandler.h"


class Logger{
    LogHandler* handler;

    // Read by every logging thread, written by setThreshold(). Non-atomic it
    // was a data race the public API openly invited, even if this particular
    // main() only wrote it between joins.
    std::atomic<int> threshold;

    Logger() : threshold(0){
        LogHandler* debugHandler = new DebugLogHandler();
        LogHandler* infoHandler = new InfoLogHandler();
        LogHandler* errorHandler = new ErrorLogHandler();

        infoHandler -> setNext(errorHandler);
        debugHandler -> setNext(infoHandler);

        handler = debugHandler;
    };

    // Triggers the cascading ~LogHandler(), which deletes the rest of the chain.
    ~Logger(){
        delete handler;
    }

public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // MessageLevel, not int: the enum class exists so callers cannot pass a
    // number that is not a level.
    void setThreshold(MessageLevel level){
        threshold = getValue(level);
    }

    void addAppender(MessageLevel level, LogAppender* appender){
        for(LogHandler* h = handler; h != nullptr; h = h -> getNext()){
            if(h -> canHandle(level)){
                h -> subscribe(appender);
                return;
            }
        }
    }

    // The singleton is a function-local static, so it outlives main(). Anything
    // main() deletes must be unregistered first, otherwise the handlers keep
    // dangling appender pointers that a later log call would follow.
    // Call this before deleting any appender.
    void shutdown(){
        for(LogHandler* h = handler; h != nullptr; h = h -> getNext()){
            h -> clearAppenders();
        }
    }

    void debug(const std::string& m){
        if(threshold <= getValue(MessageLevel::DEBUG)){
            handler -> handle(Message(m, MessageLevel::DEBUG));
        }
    }

    void info(const std::string& m){
        if(threshold <= getValue(MessageLevel::INFO)){
            handler -> handle(Message(m, MessageLevel::INFO));
        }
    }

    void error(const std::string& m){
        if(threshold <= getValue(MessageLevel::ERROR)){
            handler -> handle(Message(m, MessageLevel::ERROR));
        }
    }

};

#endif
