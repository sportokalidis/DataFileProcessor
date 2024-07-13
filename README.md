# DataFileProcessor Project

## Introduction
The DataFileProcessor project aims to develop a software component to interact with various recording files (JSON, CSV, and future types). The backend will read a data file, perform a computation, and save the results in the original file.

## Plan
1. **Project Structure**

     ```
     DataFileProcessor/
     ├── CMakeLists.txt
     ├── src/
     ├── include/
     ├── data/
     ├── tests/
     ├── docs/
     └── scripts/

2. **Set up CMake Project**
   - `CMakeLists.txt` file to define the project structure and dependencies.

3. **Base Class for File Handling**
   - Implement an abstract base class with methods for reading, processing, and saving data.

4. **JSON and CSV Handlers**
   - Implement `JsonHandler` and `CsvHandler` classes derived from base class.
   - Use `nlohmann/json.hpp` for JSON parsing and C++ stl for CSV parsing.

5. **Factory Pattern**
   - Data Handeler Factory to return the appropriate handler based on file extension.

6. **Generate sample data files**:
   - Write a script in Python or C++ to generate sample JSON and CSV files.
  
7. **Write tests**:

7. **Write Documentation**:
