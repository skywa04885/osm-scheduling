//
// Created by luke on 9/15/23.
//

#include "Job.h"

Job::Job():
    mTasks()
{}

Job::Job(std::list<Task> aTasks):
    mTasks(std::move(aTasks))
{}

Job::Job(Job &&aJob) noexcept :
    mTasks(std::move(aJob.mTasks))
{}
