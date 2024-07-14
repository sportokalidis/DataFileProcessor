#ifndef JSON_FILE_HANDLER_HPP
#define JSON_FILE_HANDLER_HPP

#include "FileHandler.hpp"
#include "json.hpp"
#include <string>

class JsonFileHandler : public FileHandler {
public:
    JsonFileHandler(const std::string& filePath );

    void readData() override;
    void writeData() override;
    void process() override;

private:
    std::string filePath;
    nlohmann::json jsonData;
};

#endif // JSON_FILE_HANDLER_HPP