//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_CONFIG_H
#define BEROEPSPRODUCT_CONFIG_H

#include <list>
#include <regex>
#include <vector>

class Config {
private:
  std::map<unsigned long, std::shared_ptr<class Machine>> mMachines;
  std::list<std::shared_ptr<class Job>> mJobs;

public:
  /**
   * Creates a new config with the given machines and jobs.
   * @param aMachines the machines.
   * @param aJobs the jobs.
   */
  Config(std::map<unsigned long, std::shared_ptr<class Machine>> aMachines,
         std::list<std::shared_ptr<Job>> aJobs);

  /**
   * Parses the config from the given input string.
   * @param input the input string to parse the config from.
   * @return the parsed config.
   */
  static Config Parse(const std::string &input);

  /**
   * Parses teh config from the given file.
   * @param fileName the name of the file.
   * @return the parsed config.
   */
  static Config ParseFromFile(const std::string &fileName);

  inline std::map<unsigned long, std::shared_ptr<class Machine>>
  GetMachinesAndMove() noexcept {
    return std::move(mMachines);
  }

  inline std::list<std::shared_ptr<Job>> GetJobsAndMove() noexcept {
    return std::move(mJobs);
  }
};

#endif // BEROEPSPRODUCT_CONFIG_H
