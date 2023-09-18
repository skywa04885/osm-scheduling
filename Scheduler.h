//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_SCHEDULER_H
#define BEROEPSPRODUCT_SCHEDULER_H

#include <map>
#include <optional>
#include <tuple>
#include <vector>
#include <list>
#include <memory>

class Scheduler {
private:
  std::list<std::shared_ptr<class Job>> mJobs;
  std::map<unsigned long, std::shared_ptr<class Machine>> mMachines;
  unsigned long mCurrentTime;

public:
  Scheduler(std::list<std::shared_ptr<class Job>> aJobs,
            std::map<unsigned long, std::shared_ptr<Machine>> aMachines);

  /// Selects a job for the given machine based on the least slack algorithm.
std::optional<std::shared_ptr<class Job>>
  SelectJobForMachine(unsigned long aMachineId);

  void Schedule();
public:
  [[nodiscard]] inline const std::list<std::shared_ptr<class Job>> &GetJobs() const noexcept {
    return mJobs;
  }
};

#endif // BEROEPSPRODUCT_SCHEDULER_H
