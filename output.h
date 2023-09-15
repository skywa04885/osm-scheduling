//
// Created by eliva on 15-9-2023.
//

#ifndef BEROEPSPRODUCT_OUTPUT_H
#define BEROEPSPRODUCT_OUTPUT_H
#include <iostream>
#include <string>
#include <fstream>


class output {
public:
    output();
    virtual ~output();
    static void printOutput(unsigned short id,unsigned short starttime,unsigned short endtime);

};


#endif //BEROEPSPRODUCT_OUTPUT_H
