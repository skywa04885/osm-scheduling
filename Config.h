//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_CONFIG_H
#define BEROEPSPRODUCT_CONFIG_H

#include <regex>
#include <vector>

#include "Machine.h"

class Config
{
private:
    std::vector<Machine> mMachines;
public:
    Config();

    static void Parse(const std::string &input);
};

#endif //BEROEPSPRODUCT_CONFIG_H
