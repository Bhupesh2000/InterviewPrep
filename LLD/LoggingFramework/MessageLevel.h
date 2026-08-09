#ifndef MESSAGE_LEVEL_H
#define MESSAGE_LEVEL_H

#include <string>

enum class MessageLevel{
    DEBUG = 1,
    INFO = 2,
    ERROR = 3
};

inline int getValue(MessageLevel level){
    return static_cast<int> (level);
}

inline std::string getString(MessageLevel level){
    if(level == MessageLevel::DEBUG) return "Debug";
    else if(level == MessageLevel::INFO) return "Info";
    else if(level == MessageLevel::ERROR) return "Error";
    else return "";
}

#endif