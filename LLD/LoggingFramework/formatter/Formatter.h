#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>

#include "../Message.h"

class Formatter{
public:
    virtual ~Formatter() = default;

    // const Message& : no copy of the message on the logging path.
    // const method   : formatting is a pure read, it must not mutate the formatter.
    virtual std::string format(const Message& m) const = 0;
};

#endif
