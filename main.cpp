#include <iostream>

#include "Input.h"
#include "Output.hpp"
#include "Scheduler.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Input and output file have not been specified" << std::endl;
    return -1;
  }

  Input config = Input::ParseFromFile(argv[1]);

  Scheduler scheduler(config.GetJobsAndMove(), config.GetMachinesAndMove());
  scheduler.Schedule();

  Output output(argv[2]);

  for (std::shared_ptr<Job> job : scheduler.GetJobs())
    output << (*job);

  return 0;
}
