#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio>
#include "JsonFileHandler.hpp"
#include "CsvFileHandler.hpp"
#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include "CsvFileHandlerCreator.hpp"

class FileHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create valid test data files
        std::ofstream jsonFile("../data/GoogleTestData.json");
        jsonFile << R"([{"id": 123646, "value": 10}, {"id": 233646, "value": 20}, {"id": 345646, "value": 30}, {"id": 456646, "value": 40}])";
        jsonFile.close();

        std::ofstream csvFile("../data/GoogleTestData.csv");
        csvFile << "id,value\n12335,10\n43452,20\n56789,30\n67890,40\n";
        csvFile.close();

        // Create empty test data files
        std::ofstream emptyJsonFile("../data/EmptyData.json");
        emptyJsonFile.close();

        std::ofstream emptyCsvFile("../data/EmptyData.csv");
        emptyCsvFile.close();

        // Create invalid format test data files
        std::ofstream invalidJsonFile("../data/InvalidFormatData.json");
        invalidJsonFile << R"([{"id": 123646, "value": "not_a_number"}, {"id": 233646, "value": 20}, {"id": 345646, "value": "NaN"}, {"id": 456646, "value": 40}])";
        invalidJsonFile.close();

        std::ofstream invalidCsvFile("../data/InvalidFormatData.csv");
        invalidCsvFile << "id,value\n12335,not_a_number\n43452,20\n56789,NaN\n67890,40\n";
        invalidCsvFile.close();

        std::ofstream SingleEntryCsvFile("../data/SingleEntryCsvData.csv");
        SingleEntryCsvFile << "id,value\n12345,50\n";
        SingleEntryCsvFile.close();

        std::ofstream SingleEntryJsonFile("../data/SingleEntryJsonData.json");
        SingleEntryJsonFile << R"([{"id": 123646, "value": 10}])";
        SingleEntryJsonFile.close();
    }

    void TearDown() override {
        // Commented out to allow inspection of output files
        std::remove("../data/GoogleTestData.json");
        std::remove("../data/GoogleTestData.csv");
        std::remove("../data/EmptyData.json");
        std::remove("../data/EmptyData.csv");
        std::remove("../data/InvalidFormatData.json");
        std::remove("../data/InvalidFormatData.csv");
        std::remove("../data/SingleEntryCsvData.csv");
        std::remove("../data/SingleEntryJsonData.json");
    }
};

TEST_F(FileHandlerTest, JsonFileHandlerProcess) {
    FileHandlerCreator* creator = new JsonFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/GoogleTestData.json");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/GoogleTestData.json");
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    // Verify the last entry contains the calculated statistics
    EXPECT_NEAR(jsonData.back()["mean"].get<double>(), 25.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["median"].get<double>(), 25.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["std_dev"].get<double>(), 11.1803, 1e-4);

    delete handler;
    delete creator;
}


TEST_F(FileHandlerTest, CsvFileHandlerProcess) {
    FileHandlerCreator* creator = new CsvFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/GoogleTestData.csv");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/GoogleTestData.csv");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Verify that statistics are correctly written to the file
    EXPECT_EQ(lines.back(), "std_dev,11.1803");
    EXPECT_EQ(lines[lines.size() - 2], "median,25");
    EXPECT_EQ(lines[lines.size() - 3], "mean,25");

    delete handler;
    delete creator;
}

TEST_F(FileHandlerTest, SingleEntryCsvFile) {
    FileHandlerCreator* creator = new CsvFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/SingleEntryCsvData.csv");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/SingleEntryCsvData.csv");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    EXPECT_EQ(lines.back(), "std_dev,0");
    EXPECT_EQ(lines[lines.size() - 2], "median,50");
    EXPECT_EQ(lines[lines.size() - 3], "mean,50");

    delete handler;
    delete creator;
}

TEST_F(FileHandlerTest, SingleEntryJsonFile) {
    FileHandlerCreator* creator = new JsonFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/SingleEntryJsonData.json");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/SingleEntryJsonData.json");
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    EXPECT_NEAR(jsonData.back()["mean"].get<double>(), 10.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["median"].get<double>(), 10.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["std_dev"].get<double>(), 0.0, 1e-5);
}

TEST_F(FileHandlerTest, EmptyJsonFile) {
    FileHandlerCreator* creator = new JsonFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/EmptyData.json");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/EmptyData.json");
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    // Check that no statistics were added
    EXPECT_EQ(jsonData.size(), 0);

    delete handler;
    delete creator;
}

TEST_F(FileHandlerTest, EmptyCsvFile) {
    FileHandlerCreator* creator = new CsvFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/EmptyData.csv");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/EmptyData.csv");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Check that no statistics were added
    EXPECT_EQ(lines.size(), 0);

    delete handler;
    delete creator;
}

TEST_F(FileHandlerTest, InvalidJsonFormat) {
    FileHandlerCreator* creator = new JsonFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/InvalidFormatData.json");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/InvalidFormatData.json");
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    // Check that no statistics were added due to invalid value
    EXPECT_EQ(jsonData.size(), 4); // Only the original invalid entries

    delete handler;
    delete creator;
}

TEST_F(FileHandlerTest, InvalidCsvFormat) {
    FileHandlerCreator* creator = new CsvFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/InvalidFormatData.csv");
    handler->readData();
    handler->process();
    handler->writeData();

    std::ifstream file("../data/InvalidFormatData.csv");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    // Check that no statistics were added due to invalid value
    EXPECT_EQ(lines.size(), 5); // Only the original invalid entries
    EXPECT_EQ(lines[1], "12335,not_a_number"); // Ensure invalid line is present
    EXPECT_EQ(lines[2], "43452,20"); // Ensure valid line is present
    EXPECT_EQ(lines[3], "56789,NaN"); // Ensure another invalid line is present
    EXPECT_EQ(lines[4], "67890,40"); // Ensure last valid line is present

    delete handler;
    delete creator;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
