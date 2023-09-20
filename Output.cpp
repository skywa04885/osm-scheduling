#include "Output.hpp"
#include "Job.h"

/// Constructs a new output for the given file name.
Output::Output(const std::string &aOutputFileName)
    : mOutputFileStream(aOutputFileName, std::ios::out) {}

/// Writes a job to the output file.
Output &Output::operator<<(const Job &aJob) {
  mOutputFileStream << aJob.GetId();
  mOutputFileStream << ' ' << aJob.GetStartTime();
  mOutputFileStream << ' ' << aJob.GetEndTime() << std::endl;

  return *this;
}
