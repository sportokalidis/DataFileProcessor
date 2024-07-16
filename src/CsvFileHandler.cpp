#include "CsvFileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

// Constructor initializing member variables
CsvFileHandler::CsvFileHandler(const std::string& filePath)
    : filePath(filePath), mean(0), median(0), std_dev(0), hasInvalidData(false) {}

void CsvFileHandler::readData() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;  // Skip empty lines
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> row;
            while (std::getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            csvData.push_back(row);
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void CsvFileHandler::writeData() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const auto& row : csvData) {
            if (row.empty()) continue;  // Skip empty rows
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        // Only write statistics if there is no invalid data and valid data was processed
        if (!hasInvalidData && csvData.size() > 1) {
            file << "mean," << mean << "\n";
            file << "median," << median << "\n";
            file << "std_dev," << std_dev << "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

void CsvFileHandler::process() {
    if (csvData.size() <= 1) {
        std::cerr << "CSV data is empty or only contains header row.\n";
        return;
    }

    std::vector<double> values;
    for (size_t i = 1; i < csvData.size(); ++i) { // Skip header row
        if (csvData[i].size() < 2) {
            std::cerr << "Invalid row format in CSV file.\n";
            hasInvalidData = true;
            return;
        }
        try {
            values.push_back(std::stod(csvData[i][1]));
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid value in CSV file: " << csvData[i][1] << "\n";
            hasInvalidData = true;
            return;
        }
    }

    if (values.empty()) {
        std::cerr << "No valid data to process.\n";
        return;
    }

    calculateStatistics(values);
}

void CsvFileHandler::calculateStatistics(const std::vector<double>& values) {
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
