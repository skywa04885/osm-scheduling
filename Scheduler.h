//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_SCHEDULER_H
#define BEROEPSPRODUCT_SCHEDULER_H

#include <map>
#include <optional>
#include <tuple>
#include <vector>

#include "Job.h"
#include "Machine.h"
#include "Task.h"

class Scheduler {
private:
  std::list<std::shared_ptr<Job>> mJobs;
  std::map<unsigned long, std::shared_ptr<Machine>> mMachines;
  unsigned long mCurrentTime;

public:
  Scheduler(std::list<std::shared_ptr<Job>> aJobs,
            std::map<unsigned long, std::shared_ptr<Machine>> aMachines);

  /// Selects a job for the given machine based on the least slack algorithm.
std::optional<std::shared_ptr<Job>>
  SelectJobForMachine(unsigned long aMachineId);

  void Schedule();
};

#endif // BEROEPSPRODUCT_SCHEDULER_H
