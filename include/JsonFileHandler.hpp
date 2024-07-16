#ifndef JSON_FILE_HANDLER_HPP
#define JSON_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include "json.hpp"
#include <string>
#include <vector>

class JsonFileHandler : public FileHandler {
public:
    JsonFileHandler(const std::string& filePath);
    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath;
    nlohmann::json jsonData;
    double mean;
    double median;
    double std_dev;
    bool hasInvalidData;

    void calculateStatistics(const std::vector<double>& values);
    void setStatisticsToZero();
};

#endif // JSON_FILE_HANDLER_HPP
