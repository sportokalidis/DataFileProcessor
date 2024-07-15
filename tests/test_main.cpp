#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdio> // for std::remove

#include "JsonFileHandler.hpp"
#include "CsvFileHandler.hpp"
#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include "CsvFileHandlerCreator.hpp"

class FileHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test data files
        std::ofstream jsonFile("../data/GoogleTestData.json");
        jsonFile << R"([{"id": 123646, "value": 10}, {"id": 233646, "value": 20}])";
        jsonFile.close();

        std::ofstream csvFile("../data/GoogleTestData.csv");
        csvFile << "id,value\n12335,10\n43452,20\n";
        csvFile.close();
    }

    void TearDown() override {
        // Clean up test data files
        std::remove("../data/GoogleTestData.json");
        std::remove("../data/GoogleTestData.csv");
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

    EXPECT_NEAR(jsonData.back()["mean"].get<double>(), 15.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["median"].get<double>(), 15.0, 1e-5);
    EXPECT_NEAR(jsonData.back()["std_dev"].get<double>(), 5.0, 1e-5);

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

    EXPECT_EQ(lines.back(), "std_dev,5");
    EXPECT_EQ(lines[lines.size() - 2], "median,15");
    EXPECT_EQ(lines[lines.size() - 3], "mean,15");

    delete handler;
    delete creator;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
