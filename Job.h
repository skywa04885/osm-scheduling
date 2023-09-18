//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_JOB_H
#define BEROEPSPRODUCT_JOB_H

#include <list>
#include <memory>

#include "Task.h"

class Job {
private:
  std::list<std::shared_ptr<Task>> mTasks;
  unsigned long mStartTime;
  unsigned long mEndTime;

public:
  /// Default constructor for the job.
  Job();

  /// Constructor for the job with tasks.
  explicit Job(std::list<std::shared_ptr<Task>> aTasks);

  /// Move constructor for the job.
  Job(Job &&aJob) noexcept;

  /// Computes the sum of all the task durations.
  [[nodiscard]] unsigned long ComputeTaskDurationSum() const;

  /// Gets the list of all the tasks.
  [[nodiscard]] inline std::list<std::shared_ptr<Task>> &GetTasks() noexcept {
    return mTasks;
  }
};

#endif // BEROEPSPRODUCT_JOB_H
