#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <vector>

#include "../Message.h"
#include "../appender/LogAppender.h"

class LogHandler{
    LogHandler* next;

    // Configuration-only state. subscribe()/clearAppenders() are documented as
    // startup / shutdown operations, called from a single thread before the
    // worker threads start and after they have joined. notifyAll() therefore
    // only ever reads a vector nobody is writing.
    // The old std::mutex here was locked by subscribe() but not by notifyAll(),
    // so it cost a lock per registration and guaranteed nothing.
    std::vector<LogAppender*> observers;

public:
    LogHandler() : next(nullptr){};

    // Deletes the rest of the chain. The trigger is Logger's destructor, which
    // deletes the head - without it this cascade never ran and the whole chain
    // leaked.
    virtual ~LogHandler(){
        delete next;
    }

    void setNext(LogHandler* handler){
        next = handler;
    }

    LogHandler* getNext(){
        return next;
    }

    virtual bool canHandle(MessageLevel level) const = 0;

    void handle(const Message& m){
        if(this -> canHandle(m.getLevel())){
            notifyAll(m);
        }
        else if(next != nullptr) next -> handle(m);
    };

    // Startup only.
    void subscribe(LogAppender* appender){
        for(auto it : observers){
            if(it == appender) return;
        }
        observers.push_back(appender);
    }

    // Shutdown only. Lets the owner drop appenders while it is still alive,
    // instead of leaving the singleton holding dangling pointers.
    void clearAppenders(){
        observers.clear();
    }

protected:
    // Not part of the public API - only handle() may fan a message out.
    void notifyAll(const Message& m){
        for(auto it : observers){
            it -> appendMessage(m);
        }
    }
};

#endif
