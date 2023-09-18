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
  std::optional<unsigned long> mEndTime;
  std::weak_ptr<class Job> mJob;

public:
  /// Constructs a new task.
  Task(unsigned long mMachineId, unsigned long mDuration,
       std::weak_ptr<class Job> aJob) noexcept;

public:
  [[nodiscard]] inline std::weak_ptr<class Job> &GetJob() noexcept {
    return mJob;
  }

  [[nodiscard]] inline unsigned long GetFinishedAfterTime() const noexcept {
    return *mStartTime + mDuration;
  }

  [[nodiscard]] inline unsigned long GetRemainingTime(unsigned long aCurrentTime) const noexcept {
    return GetFinishedAfterTime() - aCurrentTime;
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

std::ostream &operator<<(std::ostream &stream, const Task &task);

#endif // BEROEPSPRODUCT_TASK_H
