//
// Created by luke on 9/15/23.
//

#include <numeric>

#include "Job.h"

/// Default constructor for the job.
Job::Job() : mTasks(), mStartTime(0), mEndTime(0) {}

/// Constructor for the job with tasks.
Job::Job(std::list<std::shared_ptr<Task>> aTasks)
    : mTasks(std::move(aTasks)), mStartTime(0), mEndTime(0) {}

/// Move constructor for the job.
Job::Job(Job &&aJob) noexcept
    : mTasks(std::move(aJob.mTasks)), mStartTime(aJob.mStartTime),
      mEndTime(aJob.mEndTime) {}

/// Computes the sum of all the task durations.
[[nodiscard]] unsigned long Job::ComputeTaskDurationSum() const {
  const auto accumulator =
      [](unsigned long sum,
         const std::shared_ptr<Task> &task) -> unsigned long {
    return sum + task->GetDuration();
  };

  return std::accumulate(mTasks.cbegin(), mTasks.cend(), 0UL, accumulator);
}
