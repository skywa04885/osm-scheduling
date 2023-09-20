//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_TASK_H
#define BEROEPSPRODUCT_TASK_H

#include <iostream>
#include <memory>
#include <optional>

class Task {
private:
  unsigned long mMachineId;
  unsigned long mDuration;
  unsigned long mTaskNo;
  std::optional<unsigned long> mStartTime;
  std::weak_ptr<class Job> mJob;

public:
  /// Constructs a new task.
  Task(unsigned long mMachineId, unsigned long mDuration, unsigned long mTaskNo,
       std::weak_ptr<class Job> aJob) noexcept;

public:
  /// Gets the job.
  [[nodiscard]] inline std::weak_ptr<class Job> &GetJob() noexcept {
    return mJob;
  }

  /// Gets the end time of the task.
  [[nodiscard]] inline unsigned long GetEndTime() const noexcept {
    return GetStartTime() + mDuration;
  }

  /// Gets the remaining time of the task.
  [[nodiscard]] inline unsigned long GetRemainingTime(unsigned long aCurrentTime) const noexcept {
    return GetEndTime() - aCurrentTime;
  }

  /// Gets the machine id.
  [[nodiscard]] inline unsigned long GetMachineId() const noexcept {
    return mMachineId;
  }

  /// Gets the duration.
  [[nodiscard]] inline unsigned long GetDuration() const noexcept {
    return mDuration;
  }

  /// Gets the task no.
  [[nodiscard]] inline unsigned long GetTaskNo() const noexcept {
    return mTaskNo;
  }

  /// Checks if the start time has a value.
  [[nodiscard]] inline bool HasStartTime() const noexcept {
    return mStartTime.has_value();
  }

  /// Sets the start time.
  inline void SetStartTime(unsigned long aStartTime) noexcept {
    mStartTime = aStartTime;
  }

  /// Gets the start time.
  [[nodiscard]] inline unsigned long GetStartTime() const {
    if (not HasStartTime()) {
      throw std::runtime_error("Start time used but not set");
    }

    return *mStartTime;
  }
};

/// Output stream overload for task.
std::ostream &operator<<(std::ostream &stream, const Task &task);

#endif // BEROEPSPRODUCT_TASK_H
