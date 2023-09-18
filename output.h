//
// Created by eliva on 15-9-2023.
//

#ifndef BEROEPSPRODUCT_OUTPUT_H
#define BEROEPSPRODUCT_OUTPUT_H
#include <iostream>
#include <string>
#include <fstream>
#include "Job.h"

class output {
public:
    output();
    virtual ~output();
    static void printOutput(unsigned short id,unsigned short starttime,unsigned short endtime);
    static void printOutput(Job job);

//
};


#endif //BEROEPSPRODUCT_OUTPUT_H
