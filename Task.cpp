//
// Created by luke on 9/15/23.
//

#include "Task.h"

Task::Task(unsigned long mMachineId, unsigned long mDuration) noexcept
    : mMachineId(mMachineId), mDuration(mDuration), mStartTime(std::nullopt),
      mEndTime(std::nullopt) {}

std::ostream &operator<<(std::ostream &stream, const Task &task) {
  stream << "Task {";
  stream << " Duration: " << task.GetDuration() << ", ";
  stream << " MachineID: " << task.GetMachineId();
  stream << " }";

  return stream;
}
