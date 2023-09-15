//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_CONFIG_H
#define BEROEPSPRODUCT_CONFIG_H

#include <regex>
#include <vector>
#include <list>

#include "Machine.h"
#include "Job.h"

class Config
{
private:
    std::vector<Machine> mMachines;
    std::list<Job> mJobs;
public:
    Config(std::vector<Machine> aMachines, std::list<Job> aJobs);

    static Config Parse(const std::string &input);
};

#endif //BEROEPSPRODUCT_CONFIG_H
