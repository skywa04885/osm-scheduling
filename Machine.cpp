//
// Created by luke on 9/15/23.
//

#include "Machine.h"

Machine::Machine(unsigned long aId) : mId(aId), mActiveTask(std::nullopt) {}

std::ostream &operator<<(std::ostream &stream, const Machine &machine) {
  stream << "Machine {";
  stream << " ID: " << machine.GetId();
  stream << " }";

  return stream;
}
