#ifndef JSON_FILE_HANDLER_HPP
#define JSON_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include "json.hpp"
#include <string>
#include <vector>

// JsonFileHandler class inherits from FileHandler to handle JSON file operations
class JsonFileHandler : public FileHandler {
public:
    // Constructor that initializes the file path
    JsonFileHandler(const std::string& filePath);

    // Override methods to read, write, and process JSON data
    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath; // Path to the JSON file
    nlohmann::json jsonData; // Container for JSON data
    double mean;
    double median;
    double std_dev;
    bool hasInvalidData; // Flag to indicate presence of invalid data

    // Method to calculate statistics (mean, median, std deviation)
    void calculateStatistics(const std::vector<double>& values);
};

#endif // JSON_FILE_HANDLER_HPP
