//
// Created by luke on 9/15/23.
//

#include <numeric>

#include "Job.h"
#include "Task.h"

/// Default constructor for the job.
Job::Job(unsigned long aId)
    : mId(aId), mTasks(), mStartTime(std::nullopt), mEndTime(std::nullopt) {}

/// Constructor for the job with tasks.
Job::Job(unsigned long aId, std::list<std::shared_ptr<Task>> aTasks)
    : mId(aId), mTasks(std::move(aTasks)), mEndTime(std::nullopt) {}

/// Move constructor for the job.
Job::Job(Job &&aJob) noexcept
    : mId(aJob.mId), mTasks(std::move(aJob.mTasks)),
      mStartTime(aJob.mStartTime),
      mEndTime(aJob.mEndTime) {}

/// Computes the sum of all the task durations.
[[nodiscard]] unsigned long Job::ComputeTaskDurationSum() const {
  return std::accumulate(
      mTasks.cbegin(), mTasks.cend(), 0UL,
      [](unsigned long sum, const std::shared_ptr<Task> &task)
          -> unsigned long { return sum + task->GetDuration(); });
}

/// Output stream overload to display job.
std::ostream &operator << (std::ostream &aStream, const Job &aJob) {
  aStream << aJob.GetId();
  aStream << ' ' << aJob.GetStartTime();
  aStream << ' ' << aJob.GetEndTime();

  return aStream;
}

