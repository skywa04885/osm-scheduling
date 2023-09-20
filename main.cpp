#include <iostream>

#include "Input.h"
#include "Job.h"
#include "Scheduler.h"
#include "ToUML.h"

int main(int argc, char *argv[]) {
  // Makes sure the arguments are specified.
  if (argc < 2) {
    std::cerr << "Input file has not been specified" << std::endl;
    return -1;
  }

  // Loads the input from the file.
  Input input = Input::ParseFromFile(argv[1]);

  // Creates the scheduler and performs the scheduling.
  Scheduler scheduler(input.GetJobsAndMove(), input.GetMachinesAndMove());
  scheduler.Schedule();

  // Prints the output.
  for (const std::shared_ptr<Job> &job : scheduler.GetJobs())
    std::cout << (*job) << std::endl;

  ToUML toUml("../test.plantuml");
  toUml.Render(scheduler.GetMachines(), scheduler.GetTasks());

  return 0;
}
