#ifndef CSV_FILE_HANDLER_HPP
#define CSV_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include <string>
#include <vector>

class CsvFileHandler : public FileHandler {
public:
    CsvFileHandler(const std::string& filePath);
    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath;
    std::vector<std::vector<std::string>> csvData;
    double mean;
    double median;
    double std_dev;
    bool hasInvalidData;

    void calculateStatistics(const std::vector<double>& values);
};

#endif // CSV_FILE_HANDLER_HPP
