#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include "CsvFileHandler.hpp"
#include "CsvFileHandlerCreator.hpp"
#include <iostream>
#include <string>

std::string getFileExtension(const std::string& filePath) {
    size_t dotPosition = filePath.find_last_of('.');
    if (dotPosition != std::string::npos) {
        return filePath.substr(dotPosition+1);
    }
    return ""; // Return empty string if no extension found
}

int main() {
    std::string filePath = "../data/TestData.csv";
    std::string extension = getFileExtension(filePath);

    FileHandlerCreator *creator = nullptr;

    if(extension == "json") {
        creator = new JsonFileHandlerCreator();
    }
    else if(extension == "csv") {
        creator = new CsvFileHandlerCreator();
    }
    

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
        std::cerr << "Unsupported file type.\n";
    }

    return 0;
}