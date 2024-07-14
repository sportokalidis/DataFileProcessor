#ifndef FILE_HANDLER_CREATOR_HPP
#define FILE_HANDLER_CREATOR_HPP

#include "FileHandler.hpp"
#include <string>

class FileHandlerCreator {
public:
    virtual ~FileHandlerCreator() = default;
    virtual FileHandler* createFileHandler(const std::string &filePath) = 0; 
};

#endif // FILE_HANDLER_CREATOR_HPP