#include <iostream>

#include "Config.h"

int main() {
    try {
        Config::Parse("0 12\r\n0 55\r\n");
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
