#include "JsonFileHandler.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

// Constructor initializing member variables
JsonFileHandler::JsonFileHandler(const std::string& filePath)
    : filePath(filePath), mean(0), median(0), std_dev(0), hasInvalidData(false) {}

void JsonFileHandler::readData() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        try {
            file >> jsonData;
        }
        catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
            jsonData = nlohmann::json::array(); // Set to empty array on parse error
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void JsonFileHandler::writeData() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void JsonFileHandler::process() {
    if (jsonData.empty()) {
        std::cerr << "JSON data is empty.\n";
        return;
    }

    std::vector<double> values;
    for (const auto& item : jsonData) {
        try {
            values.push_back(item.at("value").get<double>());
        }
        catch (const nlohmann::json::type_error& e) {
            std::cerr << "Invalid value in JSON file: " << e.what() << "\n";
            hasInvalidData = true;
            return;
        }
    }

    if (values.empty()) {
        std::cerr << "No valid data to process.\n";
        return;
    }

    calculateStatistics(values);
    
    nlohmann::json stats = {
        {"mean", mean},
        {"median", median},
        {"std_dev", std_dev}
    };

        
    jsonData.push_back(stats);
}

void JsonFileHandler::calculateStatistics(const std::vector<double>& values) {
    if (values.empty()) return;

    // Calculate mean
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    mean = sum / values.size();

    // Sort values to calculate median
    std::vector<double> sorted_values = values;
    std::sort(sorted_values.begin(), sorted_values.end());

    // Calculate median
    if (sorted_values.size() % 2 == 0) {
        median = (sorted_values[sorted_values.size() / 2 - 1] + sorted_values[sorted_values.size() / 2]) / 2;
    }
    else {
        median = sorted_values[sorted_values.size() / 2];
    }

    // Calculate standard deviation
    double sq_sum = std::inner_product(values.begin(), values.end(), values.begin(), 0.0);
    std_dev = std::sqrt(sq_sum / values.size() - mean * mean);
}
