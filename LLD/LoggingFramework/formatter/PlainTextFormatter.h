#ifndef PLAIN_TEXT_FORMATTER_H
#define PLAIN_TEXT_FORMATTER_H

#include "./Formatter.h"
#include "../TimeUtil.h"

class PlainTextFormatter : public Formatter{
public:
    // One record, one line, terminated by exactly one '\n' so records from
    // different threads can never run into each other.
    std::string format(const Message& m) const override{
        return formatTimestamp(m.getTimeStamp())
             + " [" + getString(m.getLevel()) + "] : "
             + m.getMessageString() + "\n";
    }
};

#endif
