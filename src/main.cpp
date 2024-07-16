#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include "CsvFileHandler.hpp"
#include "CsvFileHandlerCreator.hpp"
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "json.hpp"

std::string getFileExtension(const std::string& filePath) {
    size_t dotPosition = filePath.find_last_of('.');
    if (dotPosition != std::string::npos) {
        return filePath.substr(dotPosition+1);
    }
    return ""; // Return empty string if no extension found
}

// Function to generate a random JSON file
void randomJsonFileGenerator(const std::string& fileName, int numOfEntries) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idDist(1000, 9999);
    std::uniform_real_distribution<> valueDist(1.0, 100.0);

    nlohmann::json jsonData;
    for (int i = 0; i < numOfEntries; ++i) {
        jsonData.push_back({
            {"id", idDist(gen)},
            {"value", valueDist(gen)}
        });
    }

    std::ofstream file("../data/" + fileName);
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
        std::cout << "Random JSON file generated: " << fileName << std::endl;
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

// Function to generate a random CSV file
void randomCsvFileGenerator(const std::string& fileName, int numOfEntries) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> idDist(1000, 9999);
    std::uniform_real_distribution<> valueDist(1.0, 100.0);

    std::ofstream file("../data/" + fileName);
    if (file.is_open()) {
        file << "id,value\n";
        for (int i = 0; i < numOfEntries; ++i) {
            file << idDist(gen) << "," << valueDist(gen) << "\n";
        }
        file.close();
        std::cout << "Random CSV file generated: " << fileName << std::endl;
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Hardcoded calls to generate random files
    randomJsonFileGenerator("randomData.json", 10);
    randomCsvFileGenerator("randomData.csv", 10);

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1]; // "../data/TestData.csv";
    std::string extension = getFileExtension(filePath);

    FileHandlerCreator *creator = nullptr;

    if(extension == "json") {
        creator = new JsonFileHandlerCreator();
    }
    else if(extension == "csv") {
        creator = new CsvFileHandlerCreator();
    }
    

    if(creator) {
        FileHandler* handler = creator->createFileHandler(filePath);
        if(handler) {
            handler->readData();
            handler->process();
            handler->writeData();

            delete handler;
        }
        else {
            std::cerr << "Failed to create file handler.\n";
        }
        delete creator;
    }
    else {
        std::cerr << "Unsupported file type.\n";
    }

    return 0;
}