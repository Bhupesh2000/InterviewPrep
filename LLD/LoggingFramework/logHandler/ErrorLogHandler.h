#ifndef ERROR_LOG_HANDLER_H
#define ERROR_LOG_HANDLER_H

#include "./LogHandler.h"

class ErrorLogHandler : public LogHandler{
public:
    bool canHandle(MessageLevel level) const override{
        return level == MessageLevel::ERROR;
    }  
};

#endif