#ifndef CSV_FILE_HANDLER_HPP
#define CSV_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include <string>
#include <vector>

class CsvFileHandler : public FileHandler {
public:
    CsvFileHandler(const std::string &filePath);
    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath;
    std::vector<std::vector<std::string>> csvData;
};



#endif // CSV_FILE_HANDLER_HPP