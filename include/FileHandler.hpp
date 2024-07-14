#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>

class FileHandler {
public:
    virtual void readData() = 0;
    virtual void writeData() = 0;
    virtual void process() = 0; 

    virtual ~FileHandler() = default;
};

#endif // fILe_HANDLER_HPP