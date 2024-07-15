#include "CsvFileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>  // Include this header for accumulate and inner_product

CsvFileHandler::CsvFileHandler(const std::string& filePath) : filePath(filePath), mean(0), median(0), std_dev(0) {}

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

    // Debug print
    /*std::cout << "Read CSV Data:" << std::endl;
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }*/
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
        file << "mean," << mean << "\n";
        file << "median," << median << "\n";
        file << "std_dev," << std_dev << "\n";
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
            return;
        }
        values.push_back(std::stod(csvData[i][1]));
    }
    calculateStatistics(values);

    /*csvData.push_back({ "mean", std::to_string(mean) });
    csvData.push_back({ "median", std::to_string(median) });
    csvData.push_back({ "std_dev", std::to_string(std_dev) });*/
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
