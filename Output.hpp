#pragma once

#ifndef BEROEPSPRODUCT_OUTPUT_H
#define BEROEPSPRODUCT_OUTPUT_H

#include <fstream>

#include "Job.h"

class Output
{
private:
  std::ofstream mOutputFileStream;
public:
  Output(const std::string &aOutputFileName);

  Output &operator << (const Job &aJob);
};

#endif // BEROEPSPRODUCT_OUTPUT_H

