//
// Created by luke on 9/15/23.
//

#include <iostream>

#include "Config.h"

Config::Config():
    mMachines()
{}

void Config::Parse(const std::string &input) {
    std::vector<Machine> machines = {};

    const std::basic_regex<char> lineRegex(R"((.*)(\r\n|$))",
                                           std::regex_constants::ECMAScript);
    const std::basic_regex<char> configRegex(R"(^([0-9]+)\s+([0-9]+)\s*$)",
                                       std::regex_constants::ECMAScript);
    const std::basic_regex<char> taskRegex(R"(([0-9]+)\s+([0-9]+)\s*)",
                                     std::regex_constants::ECMAScript);

    std::basic_string<char> line;
    std::cmatch match;

    std::sregex_iterator it(input.begin(), input.end(), lineRegex);
    std::sregex_iterator end{};

    if (it == end) {
        throw std::runtime_error("Input does not contain config line");
    }

    line = it->str(1);

    if (not std::regex_match(line.c_str(), match, configRegex)) {
        throw std::runtime_error("Input does not contain valid config line");
    }

    const unsigned long jobCount = std::stoul(match.str(1));
    const unsigned long machineCount = std::stoul(match.str(2));



    machines.reserve(machineCount);
    for (unsigned long machineId = 0; machineId < machineCount; ++machineId) {
        machines.emplace_back(machineId);
    }



//    for (; std::getline(inputStream, line, '\n');) {
//        if (line.back() == '\r') {
//            line.pop_back();
//        }
//
//
//    }
}