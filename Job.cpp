//
// Created by luke on 9/15/23.
//

#include <numeric>

#include "Job.h"

/// Default constructor for the job.
Job::Job() : mTasks(), mStartTime(std::nullopt), mEndTime(std::nullopt) {}

/// Constructor for the job with tasks.
Job::Job(std::list<std::shared_ptr<Task>> aTasks)
    : mTasks(std::move(aTasks)), mStartTime(std::nullopt),
      mEndTime(std::nullopt) {}

/// Move constructor for the job.
Job::Job(Job &&aJob) noexcept
    : mTasks(std::move(aJob.mTasks)), mStartTime(std::move(aJob.mStartTime)),
      mEndTime(std::move(aJob.mEndTime)) {}

/// Computes the sum of all the task durations.
[[nodiscard]] unsigned long Job::ComputeTaskDurationSum() const {
  return std::accumulate(
      mTasks.cbegin(), mTasks.cend(), 0UL,
      [](unsigned long sum, const std::shared_ptr<Task> &task)
          -> unsigned long { return sum + task->GetDuration(); });
}
