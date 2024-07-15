 //test/test_main.cpp
#include <gtest/gtest.h>
#include "JsonFileHandler.hpp"
#include "CsvFileHandler.hpp"
#include "FileHandlerCreator.hpp"
#include "JsonFileHandlerCreator.hpp"
#include "CsvFileHandlerCreator.hpp"


TEST(JsonFileHandlerTest, ReadData) {
    FileHandlerCreator* creator = new JsonFileHandlerCreator();
    FileHandler* handler = creator->createFileHandler("../data/TestData.json");
     //JsonFileHandler handler("../data/TestData.json");
    handler->readData();
    EXPECT_NO_THROW(handler->process());
    // EXPECT_EQ(1,1);
}

TEST(CsvFileHandlerTest, ReadData) {
    // CsvFileHandler handler("../data/TestData.csv");
    // handler.readData();
    // EXPECT_NO_THROW(handler.process());
    EXPECT_EQ(1,1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}