#pragma once

#ifndef BEROEPSPRODUCT_OUTPUT_H
#define BEROEPSPRODUCT_OUTPUT_H

#include <fstream>

class Output {
private:
  std::ofstream mOutputFileStream;

public:
  /// Constructs a new output for the given file name.
  Output(const std::string &aOutputFileName);

  /// Writes a job to the output file.
  Output &operator<<(const class Job &aJob);
};

#endif // BEROEPSPRODUCT_OUTPUT_H
