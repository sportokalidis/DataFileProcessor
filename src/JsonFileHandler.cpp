#include "JsonFileHandler.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

JsonFileHandler::JsonFileHandler(const std::string& filePath) : filePath(filePath), mean(0), median(0), std_dev(0) {}

void JsonFileHandler::readData() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> jsonData;
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void JsonFileHandler::writeData() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << jsonData.dump(4);  // Pretty print with 4 spaces
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void JsonFileHandler::process() {
    std::vector<double> values;
    for (const auto& item : jsonData) {
        values.push_back(item["value"].get<double>());
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

    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    mean = sum / values.size();

    std::vector<double> sorted_values = values;
    std::sort(sorted_values.begin(), sorted_values.end());
    if (sorted_values.size() % 2 == 0) {
        median = (sorted_values[sorted_values.size() / 2 - 1] + sorted_values[sorted_values.size() / 2]) / 2;
    }
    else {
        median = sorted_values[sorted_values.size() / 2];
    }

    double sq_sum = std::inner_product(values.begin(), values.end(), values.begin(), 0.0);
    std_dev = std::sqrt(sq_sum / values.size() - mean * mean);
}
