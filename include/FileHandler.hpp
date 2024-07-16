#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <string>

// Abstract base class for file handlers
class FileHandler {
public:

    // Pure virtual methods to be implemented by derived classes
    virtual void readData() = 0;
    virtual void writeData() = 0;
    virtual void process() = 0; 

    // Virtual destructor
    virtual ~FileHandler() = default;
};

#endif // fILe_HANDLER_HPP