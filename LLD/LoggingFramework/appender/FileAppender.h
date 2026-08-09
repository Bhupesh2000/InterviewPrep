#ifndef FILE_APPENDER_H
#define FILE_APPENDER_H

#include <fstream>
#include <iostream>
#include <string>

#include "./LogAppender.h"

class FileAppender : public LogAppender{
    std::ofstream out;

public:
    // Writes to a real file. The old stub wrote to std::cout, which is the very
    // destination ConsoleAppender guards with a *different* mutex - two locks
    // over one resource protect nothing, and records interleaved mid-line.
    FileAppender(Formatter* formatter, const std::string& fileName) :
        LogAppender(formatter), out(fileName, std::ios::app){
        if(!out){
            std::cerr << "FileAppender : could not open " << fileName << "\n";
        }
    };

    void appendMessage(const Message& m) override{
        std::string record = formatter->format(m);

        std::lock_guard<std::mutex> lock(mtx);
        if(out){
            out << record;
            out.flush();
        }
    }
};

#endif
