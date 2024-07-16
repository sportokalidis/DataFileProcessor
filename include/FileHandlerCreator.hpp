#ifndef FILE_HANDLER_CREATOR_HPP
#define FILE_HANDLER_CREATOR_HPP

#include "FileHandler.hpp"
#include <string>

// Abstract factory class for creating FileHandler objects
class FileHandlerCreator {
public:
    virtual ~FileHandlerCreator() = default;

    // Pure virtual method to create a FileHandler
    virtual FileHandler* createFileHandler(const std::string &filePath) = 0; 
};

#endif // FILE_HANDLER_CREATOR_HPP