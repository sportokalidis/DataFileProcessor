#ifndef CSV_FILE_HANDLER_CREATOR_HPP
#define CSV_FILE_HANDLER_CREATOR_HPP

#include "FileHandlerCreator.hpp"
#include "CsvFileHandler.hpp"

// Concrete factory class for creating CsvFileHandler objects
class CsvFileHandlerCreator : public FileHandlerCreator {
public: 
    FileHandler* createFileHandler(const std::string &filePath) override {
        return new CsvFileHandler(filePath);
    }
};


#endif CSV_FILE_HANDLER_CREATOR_HPP