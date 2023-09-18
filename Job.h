//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_JOB_H
#define BEROEPSPRODUCT_JOB_H

#include <list>
#include <memory>
#include <optional>

#include "Task.h"

class Job {
private:
  std::list<std::shared_ptr<Task>> mTasks;
  std::optional<unsigned long> mStartTime;
  std::optional<unsigned long> mEndTime;

public:
  /// Default constructor for the job.
  Job();

  /// Constructor for the job with tasks.
  explicit Job(std::list<std::shared_ptr<Task>> aTasks);

  /// Move constructor for the job.
  Job(Job &&aJob) noexcept;

  /// Computes the sum of all the task durations.
  [[nodiscard]] unsigned long ComputeTaskDurationSum() const;

public:
  /// Gets the list of all tasks.
  [[nodiscard]] inline std::list<std::shared_ptr<Task>> &GetTasks() noexcept {
    return mTasks;
  }

  /// Checks if the start time has a value.
  [[nodiscard]] inline bool HasStartTime() const noexcept {
    return mStartTime.has_value();
  }

  /// Checks if the end time has a value.
  [[nodiscard]] inline bool HasEndTime() const noexcept {
    return mEndTime.has_value();
  }

  /// Sets the start time.
  inline void SetStartTime(unsigned long aStartTime) noexcept {
    mStartTime = aStartTime;
  }

  /// Sets the start time.
  inline void SetEndTime(unsigned long aEndTime) noexcept {
    mEndTime = aEndTime;
  }

  /// Gets the start time.
  [[nodiscard]] inline unsigned long GetStartTime() const noexcept {
    return *mStartTime;
  }

  /// Gets the end time.
  [[nodiscard]] inline unsigned long GetEndTime() const noexcept {
    return *mEndTime;
  }
};

#endif // BEROEPSPRODUCT_JOB_H
