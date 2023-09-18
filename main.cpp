#include <iostream>

#include "Config.h"
#include "Output.hpp"
#include "Scheduler.h"

int main(int argc, char *argv[]) {
  // Makes sure that the config file is given.
  if (argc < 3) {
    std::cerr << "Input and output file have not been specified" << std::endl;
    return -1;
  }

  // Parses the config from the file.
  Config config = Config::ParseFromFile(argv[1]);

  Scheduler scheduler(config.GetJobsAndMove(), config.GetMachinesAndMove());
  scheduler.Schedule();

  Output output(argv[2]);

  std::for_each(
      scheduler.GetJobs().cbegin(), scheduler.GetJobs().cend(),
      [&output](const std::shared_ptr<Job> &job) { output << (*job); });

  return 0;
}
