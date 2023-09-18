//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_TASK_H
#define BEROEPSPRODUCT_TASK_H

#include <iostream>

class Task {
private:
  unsigned long mMachineId;
  unsigned long mDuration;

public:
  Task(unsigned long mMachineId, unsigned long mDuration) noexcept;

  [[nodiscard]] inline unsigned long GetMachineId() const noexcept {
    return mMachineId;
  }

  [[nodiscard]] inline unsigned long GetDuration() const noexcept {
    return mDuration;
  }

  unsigned long GetSlackTime(unsigned long currentTime) const noexcept;
};

std::ostream &operator << (std::ostream &stream, const Task &task);

#endif // BEROEPSPRODUCT_TASK_H
