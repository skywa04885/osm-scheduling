//
// Created by luke on 9/15/23.
//

#include <fstream>
#include <iostream>
#include <ostream>

#include "Input.h"
#include "Job.h"
#include "Machine.h"
#include "Task.h"

/// Creates a new input instance.
Input::Input(std::map<unsigned long, std::shared_ptr<Machine>> aMachines,
             std::list<std::shared_ptr<Job>> aJobs)
    : mMachines(std::move(aMachines)), mJobs(std::move(aJobs)) {}

/// Parses the input from the given string.
Input Input::Parse(const std::string &input) {
  // Initializes the regular expression related stuffs.
  const std::basic_regex<char> lineRegex(R"((.*)(\r\n|\n))",
                                         std::regex_constants::ECMAScript);
  const std::basic_regex<char> configRegex(R"(^([0-9]+)\s+([0-9]+)\s*$)",
                                           std::regex_constants::ECMAScript);
  const std::basic_regex<char> taskRegex(R"(([0-9]+)\s+([0-9]+)\s*)",
                                         std::regex_constants::ECMAScript);
  const std::sregex_iterator end{};

  // Initializes the commonly used variables.
  std::map<unsigned long, std::shared_ptr<Machine>> machines = {};
  std::basic_string<char> line, task;
  std::list<std::shared_ptr<Job>> jobs = {};
  std::cmatch match;

  // Creates an iterator that iterates over all the lines of the config.
  std::sregex_iterator lineRegexIterator(input.begin(), input.end(), lineRegex);
  if (lineRegexIterator == end) {
    throw std::runtime_error("Input does not contain config line");
  }

  // Gets the first line and attempts to get the basic configuration from it.
  line = lineRegexIterator->str(1);
  if (not std::regex_match(line.c_str(), match, configRegex)) {
    throw std::runtime_error("Input does not contain valid config line");
  }

  // Gets the job and machine count from the basic configuration.
  const unsigned long jobCount = std::stoul(match.str(1));
  const unsigned long machineCount = std::stoul(match.str(2));

  // Creates all the jobs and the tasks that belong to them. We assume that
  //  the number of jobs in the config are accurate, otherwise we'll throw
  //  an error while we're reading.
  for (unsigned long jobNo = 0; jobNo < jobCount; ++jobNo) {
    // Attempts to get the next line.
    if ((++lineRegexIterator) == end) {
      throw std::runtime_error("Job line missing from file");
    }
    line = lineRegexIterator->str(1);

    std::shared_ptr<Job> job = std::make_shared<Job>(jobNo);

    // Creates all the tasks that belong to the job.
    for (std::sregex_iterator taskIterator(line.begin(), line.end(), taskRegex);
         taskIterator != end; ++taskIterator) {
      const unsigned long taskMachineId = std::stoul(taskIterator->str(1));
      const unsigned long taskDuration = std::stoul(taskIterator->str(2));
      job->GetTasks().push_back(
          std::make_shared<Task>(taskMachineId, taskDuration, job));
      if (machines.find(taskMachineId) == machines.end())
        machines[taskMachineId] = std::make_shared<Machine>(taskMachineId);
    }

    // Creates the job with the just created tasks.
    jobs.push_back(std::move(job));
  }

  // Makes sure that the number of found machines equals the machine count.
  if (machineCount != machines.size()) {
    throw std::runtime_error("Machine count mismatch");
  }

  // Creates the config.
  return {std::move(machines), std::move(jobs)};
}

/// Parses the input from the given file.
Input Input::ParseFromFile(const std::string &fileName) {
  // Attempts to open the config file.
  std::ifstream configFileStream(fileName, std::ios::in);
  if (!configFileStream.is_open()) {
    throw std::runtime_error("Failed to open input file");
  }

  // Gets the size of the file by computing the difference between the end and
  //  start of the file.
  configFileStream.seekg(0, std::ios::end);
  const long end = configFileStream.tellg();
  configFileStream.seekg(0, std::ios::beg);
  const long start = configFileStream.tellg();
  const long fileSize = end - start;

  // Reads the file into a temporary buffer and converts it into a string after.
  std::unique_ptr<char[]> fileContentsBuffer =
      std::make_unique<char[]>(fileSize);
  configFileStream.read(fileContentsBuffer.get(), fileSize);
  std::basic_string<char> fileContents(fileContentsBuffer.get(), fileSize);

  // Parses and returns the config file.
  return Input::Parse(fileContents);
}
