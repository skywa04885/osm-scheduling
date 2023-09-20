//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_INPUT_H
#define BEROEPSPRODUCT_INPUT_H

#include <list>
#include <regex>
#include <vector>

class Input {
private:
  std::map<unsigned long, std::shared_ptr<class Machine>> mMachines;
  std::list<std::shared_ptr<class Job>> mJobs;

public:
  /// Creates a new input instance.
  Input(std::map<unsigned long, std::shared_ptr<class Machine>> aMachines,
        std::list<std::shared_ptr<Job>> aJobs);

  /// Parses the input from the given string.
  static Input Parse(const std::string &input);

  /// Parses the input from the given file.
  static Input ParseFromFile(const std::string &fileName);

  /// Moves the machines out of the input so they can be used.
  inline std::map<unsigned long, std::shared_ptr<class Machine>>
  GetMachinesAndMove() noexcept {
    return std::move(mMachines);
  }

  /// Moves the jobs out of the input so they can be used.
  inline std::list<std::shared_ptr<Job>> GetJobsAndMove() noexcept {
    return std::move(mJobs);
  }
};

#endif // BEROEPSPRODUCT_INPUT_H
