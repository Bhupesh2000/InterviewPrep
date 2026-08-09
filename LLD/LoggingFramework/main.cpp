#include <iostream>
#include <thread>
#include <vector>

#include "./Logger.h"
#include "./MessageLevel.h"
#include "./formatter/PlainTextFormatter.h"
#include "./formatter/XMLFormatter.h"
#include "./appender/ConsoleAppender.h"
#include "./appender/FileAppender.h"

void worker(int id){
    Logger& logger = Logger::getInstance();

    logger.debug("Thread " + std::to_string(id) + " : connecting to the database");
    logger.info("Thread " + std::to_string(id) + " : request handled");
    logger.error("Thread " + std::to_string(id) + " : failed to write to disk");
}

int main(){
    Formatter* plainText = new PlainTextFormatter();
    Formatter* xml = new XMLFormatter();

    LogAppender* console = new ConsoleAppender(plainText);
    LogAppender* file = new FileAppender(xml, "app.log");

    Logger& logger = Logger::getInstance();

    // Configuration happens here, on one thread, before any worker starts.
    // Debug and info go to the console, errors go to both console and file
    logger.addAppender(MessageLevel::DEBUG, console);
    logger.addAppender(MessageLevel::INFO, console);
    logger.addAppender(MessageLevel::ERROR, console);
    logger.addAppender(MessageLevel::ERROR, file);

    std::cout << "----- threshold = DEBUG -----\n";
    logger.setThreshold(MessageLevel::DEBUG);

    std::vector<std::thread> threads;
    for(int i = 1; i <= 3; i++){
        threads.push_back(std::thread(worker, i));
    }
    for(auto& t : threads){
        t.join();
    }

    std::cout << "\n----- threshold = ERROR -----\n";
    logger.setThreshold(MessageLevel::ERROR);

    threads.clear();
    for(int i = 4; i <= 6; i++){
        threads.push_back(std::thread(worker, i));
    }
    for(auto& t : threads){
        t.join();
    }

    // All threads have joined, so this is single threaded again. Unregister the
    // appenders before destroying them - the Logger singleton outlives main()
    // and must not be left holding pointers to freed objects.
    logger.shutdown();

    delete console;
    delete file;
    delete plainText;
    delete xml;

    return 0;
}
