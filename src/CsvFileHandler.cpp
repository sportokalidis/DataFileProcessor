#include "CsvFileHandler.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

CsvFileHandler::CsvFileHandler(const std::string& filePath) : filePath(filePath) {}

void CsvFileHandler::readData() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<std::string> row;
            while (std::getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            csvData.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "The file is not open: " << filePath << std::endl;  
    }
}

void CsvFileHandler::writeData() {
    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const auto& row : csvData) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        file.close();
    } else {
        std::cerr << "The file is not open: " << filePath << std::endl;  
    }
}

void CsvFileHandler::process() {
    // Example computation: Add a new column with a computed value
    for (auto& row : csvData) {
        row.push_back("This is a TEST"); // Replace with actual computation
    }
}
