//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_MACHINE_H
#define BEROEPSPRODUCT_MACHINE_H

#include <memory>
#include <optional>
#include <ostream>

class Machine {
private:
  const unsigned long mId;
  std::optional<std::shared_ptr<class Task>> mActiveTask;

public:
  /// Createsa new machine with the given id.
  explicit Machine(unsigned long aId);

public:
  /// Gets the machine id.
  [[nodiscard]] inline unsigned long GetId() const noexcept { return mId; }

  /// If the machine has an active task.
  [[nodiscard]] inline bool HasActiveTask() const noexcept {
    return mActiveTask.has_value();
  }

  /// Gets the active task.
  [[nodiscard]] inline std::shared_ptr<class Task> &GetActiveTask() noexcept {
    return *mActiveTask;
  }

  /// Sets the active task.
  inline void SetActiveTask(std::shared_ptr<class Task> aTask) noexcept {
    mActiveTask = std::move(aTask);
  }

  /// Deletes the active task.
  inline void DeleteActiveTask() noexcept { mActiveTask = std::nullopt; }
};

std::ostream &operator<<(std::ostream &stream, const Machine &machine);

#endif // BEROEPSPRODUCT_MACHINE_H
