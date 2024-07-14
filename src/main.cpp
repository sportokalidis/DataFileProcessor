#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include <iostream>
#include <string>

int main() {
    std::string filePath = "../data/TestData.json";
    
    FileHandlerCreator *creator = new JsonFileHandlerCreator();

    if(creator) {
        FileHandler* handler = creator->createFileHandler(filePath);
        if(handler) {
            handler->readData();
            handler->process();
            handler->writeData();

            delete handler;
        }
        else {
            std::cerr << "Failed to create file handler.\n";
        }
        delete creator;
    }
    else {
        std::cerr << "Failed to create file Creator.\n";
    }

    return 0;
}