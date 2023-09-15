//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_SCHEDULER_H
#define BEROEPSPRODUCT_SCHEDULER_H

#include <map>
#include <list>

#include "Task.h"
#include "Job.h"
#include "Machine.h"

class Scheduler {
private:
    std::map<unsigned int, Machine> mMachines;
    std::list<Job> mJobs;
};


#endif //BEROEPSPRODUCT_SCHEDULER_H
