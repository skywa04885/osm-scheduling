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
    unsigned short id, starttime, endtime;
public:
    Job();

    explicit Job(std::list<Task> aTasks);

    Job(Job &&aJob) noexcept;

    unsigned short getId() const;

    unsigned short getStarttime() const;

    unsigned short getEndtime() const;

    unsigned short getId();
};


#endif //BEROEPSPRODUCT_JOB_H
