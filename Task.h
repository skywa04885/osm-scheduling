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
  std::optional<unsigned long> mStartTime;
  std::weak_ptr<class Job> mJob;

public:
  /// Constructs a new task.
  Task(unsigned long mMachineId, unsigned long mDuration,
       std::weak_ptr<class Job> aJob) noexcept;

public:
  [[nodiscard]] inline std::weak_ptr<class Job> &GetJob() noexcept {
    return mJob;
  }

  [[nodiscard]] inline unsigned long GetEndTime() const noexcept {
    return *mStartTime + mDuration;
  }

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

  /// Checks if the start time has a value.
  [[nodiscard]] inline bool HasStartTime() const noexcept {
    return mStartTime.has_value();
  }

  /// Sets the start time.
  inline void SetStartTime(unsigned long aStartTime) noexcept {
    mStartTime = aStartTime;
  }

  /// Gets the start time.
  [[nodiscard]] inline unsigned long GetStartTime() const noexcept {
    return *mStartTime;
  }
};

std::ostream &operator<<(std::ostream &stream, const Task &task);

#endif // BEROEPSPRODUCT_TASK_H
