//
// Created by luke on 9/15/23.
//

#include "Task.h"

/// Constructs a new task.
Task::Task(unsigned long mMachineId, unsigned long mDuration,
           std::weak_ptr<class Job> aJob) noexcept
    : mMachineId(mMachineId), mDuration(mDuration), mStartTime(std::nullopt),
      mJob(std::move(aJob)) {}

/// Output stream overload for task.
std::ostream &operator<<(std::ostream &stream, const Task &task) {
  stream << "Task {";
  stream << " Duration: " << task.GetDuration() << ", ";
  stream << " MachineID: " << task.GetMachineId();
  stream << " }";

  return stream;
}
