#ifndef JSON_FILE_HANDLER_CREATOR_HPP
#define JSON_FILE_HANDLER_CREATOR_HPP

#include "FileHandlerCreator.hpp"
#include "JsonFileHandler.hpp"

// Concrete factory class for creating JsonFileHandler objects
class JsonFileHandlerCreator : public FileHandlerCreator {
public: 
    // Override method to create a JsonFileHandler
    FileHandler *createFileHandler(const std::string &filePath) override {
        return new JsonFileHandler(filePath);
    }
};

#endif // FILE_HANDLER_CREATOR_HPP