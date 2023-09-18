//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_MACHINE_H
#define BEROEPSPRODUCT_MACHINE_H

#include <memory>
#include <optional>
#include <ostream>

#include "Task.h"

class Machine {
private:
  const unsigned long mId;
  std::optional<std::tuple<std::shared_ptr<Task>, unsigned long>> mActiveTask;

public:
  explicit Machine(unsigned long aId);

  [[nodiscard]] inline unsigned long GetId() const noexcept { return mId; }

  [[nodiscard]] inline bool HasActiveTask() const noexcept {
    return mActiveTask.has_value();
  }

  [[nodiscard]] inline std::tuple<std::shared_ptr<Task>, unsigned long> &GetActiveTask() noexcept {
    return *mActiveTask;
  }

  inline void SetActiveTask(std::tuple<std::shared_ptr<Task>, unsigned long> aTask) noexcept {
    mActiveTask = std::move(aTask);
  }

  inline void DeleteActiveTask() noexcept { mActiveTask = std::nullopt; }
};

std::ostream &operator << (std::ostream& stream, const Machine &machine);

#endif // BEROEPSPRODUCT_MACHINE_H
