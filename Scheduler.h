//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_SCHEDULER_H
#define BEROEPSPRODUCT_SCHEDULER_H

#include <list>
#include <map>
#include <memory>
#include <optional>
#include <tuple>
#include <vector>

class Scheduler {
private:
  std::list<std::shared_ptr<class Job>> mJobs;
  std::map<unsigned long, std::shared_ptr<class Machine>> mMachines;
  unsigned long mCurrentTime;

public:
  /// Creates a new scheduler.
  Scheduler(std::list<std::shared_ptr<class Job>> aJobs,
            std::map<unsigned long, std::shared_ptr<Machine>> aMachines);

  /// Selects a task for the given machine based on the least slack algorithm.
  std::optional<std::shared_ptr<class Task>>
  SelectTaskForMachine(unsigned long aMachineId);

  /// Stops all the tasks if they're finished.
  void StopFinishedTasks();

  /// Starts tasks.
  void StartTasks();

  /// Gets the time of the nearest event.
  std::optional<unsigned long> GetNearestEventTime();

  /// Schedules the jobs.
  void Schedule();

public:
  /// Gets the list of all jobs.
  [[nodiscard]] inline const std::list<std::shared_ptr<class Job>> &
  GetJobs() const noexcept {
    return mJobs;
  }
};

#endif // BEROEPSPRODUCT_SCHEDULER_H
