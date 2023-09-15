#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include "Config.h"

int main(int argc, char *argv[]) {
    // Makes sure that the config file is given.
    if (argc < 2) {
        std::cerr << "Configuration file has not been specified" << std::endl;
        return -1;
    }

    // Attempts to open the config file.
    std::ifstream configFileStream(argv[1], std::ios::in);
    if (!configFileStream.is_open()) {
        std::cerr << "Configuration file could not be opened" << std::endl;
        return -1;
    }

    // Gets the size of the file by computing the difference between the end and
    //  start of the file.
    configFileStream.seekg(0, std::ios::end);
    const long end = configFileStream.tellg();
    configFileStream.seekg(0, std::ios::beg);
    const long start = configFileStream.tellg();
    const long fileSize = end - start;

    // Reads the file into a temporary buffer and converts it into a string after.
    std::unique_ptr<char[]> fileContentsBuffer = std::make_unique<char[]>(fileSize);
    configFileStream.read(fileContentsBuffer.get(), fileSize);
    std::basic_string<char> fileContents(fileContentsBuffer.get(), fileSize);

    // Parses the config file.
    try {
        Config::Parse(fileContents);
    } catch (std::runtime_error &e) {
        std::cerr << "Failed to parse config, error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
