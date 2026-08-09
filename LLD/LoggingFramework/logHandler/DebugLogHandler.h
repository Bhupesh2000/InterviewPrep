#ifndef DEBUG_LOG_HANDLER_H
#define DEBUG_LOG_HANDLER_H

#include "./LogHandler.h"

class DebugLogHandler : public LogHandler{
public:
    bool canHandle(MessageLevel level) const override{
        return level == MessageLevel::DEBUG;
    }
};

#endif