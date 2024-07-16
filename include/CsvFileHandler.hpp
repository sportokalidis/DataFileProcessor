#ifndef CSV_FILE_HANDLER_HPP
#define CSV_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include <string>
#include <vector>

// CsvFileHandler class inherits from FileHandler to handle CSV file operations
class CsvFileHandler : public FileHandler {
public:
    // Constructor that initializes the file path
    CsvFileHandler(const std::string& filePath);

    // Override methods to read, write, and process CSV data
    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath; // Path to the CSV file
    std::vector<std::vector<std::string>> csvData; // Container for CSV data
    double mean;
    double median;
    double std_dev;
    bool hasInvalidData; // Flag to indicate presence of invalid data

    // Method to calculate statistics (mean, median, std deviation)
    void calculateStatistics(const std::vector<double>& values);
};

#endif // CSV_FILE_HANDLER_HPP
