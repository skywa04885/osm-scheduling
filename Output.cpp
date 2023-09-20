#include "Output.hpp"

Output::Output(const std::string &aOutputFileName)
    : mOutputFileStream(aOutputFileName, std::ios::out) {}

Output &Output::operator<<(const Job &aJob) {
  mOutputFileStream << aJob.GetId();
  mOutputFileStream << ' ' << aJob.GetStartTime();
  mOutputFileStream << ' ' << aJob.GetEndTime() << std::endl;

  return *this;
}
