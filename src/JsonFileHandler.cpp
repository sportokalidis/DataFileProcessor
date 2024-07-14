#include "JsonFileHandler.hpp"
#include <fstream>
#include <iostream>

JsonFileHandler::JsonFileHandler(const std::string &filePath) : filePath(filePath) {};

void JsonFileHandler::readData() {
    std::ifstream file(filePath);
    if(file.is_open()) {
        file >> jsonData;
        file.close();
    }
    else {
        std::cerr << "The file is not open: " << filePath << std::endl;  
    }
}

void JsonFileHandler::writeData() {
    std::ofstream file(filePath);
    if(file.is_open()) {
        file << jsonData.dump(4);
        file.close();
    }
    else {
        std::cerr << "The file is not open: " << filePath << std::endl;  
    }
}

void JsonFileHandler::process() {
    // TODO : Make something creative in this Proccess Func

    jsonData["Add a new Row for Test"] = " This is a TEST ";
}

