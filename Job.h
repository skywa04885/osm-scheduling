//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_JOB_H
#define BEROEPSPRODUCT_JOB_H

#include <list>
#include <memory>
#include <optional>
#include <ostream>

class Job {
private:
  unsigned long mId;
  std::list<std::shared_ptr<class Task>> mTasks;
  std::optional<unsigned long> mStartTime;
  std::optional<unsigned long> mEndTime;

public:
  /// Default constructor for the job.
  Job(unsigned long aId);

  /// Constructor for the job with tasks.
  explicit Job(unsigned long aId, std::list<std::shared_ptr<class Task>> aTasks);

  /// Move constructor for the job.
  Job(Job &&aJob) noexcept;

  /// Computes the sum of all the task durations.
  [[nodiscard]] unsigned long ComputeTaskDurationSum() const;

public:
  /// Gets the id.
  [[nodiscard]] inline unsigned long GetId() const noexcept {
    return mId;
  }

  /// Checcks if there are any remaining tasks.
  [[nodiscard]] inline bool HasTasks() const noexcept {
    return not mTasks.empty();
  }

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

/// Output stream overload to display job.
std::ostream &operator << (std::ostream &aStream, const Job &aJob);

#endif // BEROEPSPRODUCT_JOB_H
