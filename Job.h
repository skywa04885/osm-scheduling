//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_JOB_H
#define BEROEPSPRODUCT_JOB_H

#include <list>

#include "Job.h"
#include "Task.h"

class Job {
private:
    std::list<Task> mTasks;
public:
    Job();

    explicit Job(std::list<Task> aTasks);

    Job(Job &&aJob) noexcept;
};


#endif //BEROEPSPRODUCT_JOB_H
