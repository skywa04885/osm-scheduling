#include <iostream>
#include <fstream>
#include <string>

#include "Config.h"

int main() {
    std::ifstream ifstream("../input.txt", std::ios::in);

    if (!ifstream.is_open()) {
        throw std::runtime_error("Failed to oepn config file");
    }

    ifstream.seekg(0, std::ios::end);
    const long end = ifstream.tellg();
    ifstream.seekg(0, std::ios::beg);
    const long start = ifstream.tellg();

    const long fileSize = end - start;

    char *fileContentsBuffer = new char[fileSize];

    ifstream.read(fileContentsBuffer, fileSize);

    std::string fileContents(fileContentsBuffer, fileSize);
    delete[] fileContentsBuffer;


    try {
        Config::Parse(fileContents);
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
