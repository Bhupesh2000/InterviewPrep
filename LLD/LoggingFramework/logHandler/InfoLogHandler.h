#ifndef INFO_LOG_HANDLER_H
#define INFO_LOG_HANDLER_H

#include "./LogHandler.h"

class InfoLogHandler : public LogHandler{
public:
    bool canHandle(MessageLevel level) const override{
        return level == MessageLevel::INFO;
    }
};

#endif