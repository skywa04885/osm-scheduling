//
// Created by luke on 9/15/23.
//

#include <iostream>
#include <ostream>

#include "Config.h"
#include "Task.h"

Config::Config(std::vector<Machine> aMachines, std::list<Job> aJobs):
    mMachines(std::move(aMachines)),
    mJobs(std::move(aJobs))
{}

Config Config::Parse(const std::string &input) {
    std::vector<Machine> machines = {};
    std::list<Job> jobs = {};

    const std::basic_regex<char> lineRegex(R"((.*)(\r\n|\n))",
                                           std::regex_constants::ECMAScript);
    const std::basic_regex<char> configRegex(R"(^([0-9]+)\s+([0-9]+)\s*$)",
                                       std::regex_constants::ECMAScript);
    const std::basic_regex<char> taskRegex(R"(([0-9]+)\s+([0-9]+)\s*)",
                                     std::regex_constants::ECMAScript);

    const std::sregex_iterator end{};

    std::basic_string<char> line, task;
    std::cmatch match;

    std::sregex_iterator lineRegexIterator(input.begin(), input.end(), lineRegex);

    if (lineRegexIterator == end) {
        throw std::runtime_error("Input does not contain config line");
    }

    line = lineRegexIterator->str(1);

    if (not std::regex_match(line.c_str(), match, configRegex)) {
        throw std::runtime_error("Input does not contain valid config line");
    }

    const unsigned long jobCount = std::stoul(match.str(1));
    const unsigned long machineCount = std::stoul(match.str(2));

    for (unsigned long jobNo = 0; jobNo < jobCount; ++jobNo) {
        if ((++lineRegexIterator) == end) {
            throw std::runtime_error("Job line missing from file");
        }

        line = lineRegexIterator->str(1);

        std::list<Task> tasks = {};

        for(std::sregex_iterator taskIterator(line.begin(), line.end(), taskRegex); taskIterator != end; ++taskIterator) {
            const unsigned long taskMachineId = std::stoul(taskIterator->str(1));
            const unsigned long taskDuration = std::stoul(taskIterator->str(2));

            tasks.emplace_back(taskMachineId, taskDuration);
        }

        jobs.emplace_back(std::move(tasks));
    }

    machines.reserve(machineCount);
    for (unsigned long machineId = 0; machineId < machineCount; ++machineId) {
        machines.emplace_back();
    }

    return {std::move(machines), std::move(jobs)};
}
