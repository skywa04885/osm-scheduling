//
// Created by luke on 9/15/23.
//

#include "Scheduler.h"

#include <algorithm>
#include <iostream>
#include <tuple>

Scheduler::Scheduler(
    std::list<std::shared_ptr<Job>> aJobs,
    std::map<unsigned long, std::shared_ptr<Machine>> aMachines)
    : mJobs(aJobs), mMachines(aMachines), mCurrentTime(0UL) {}

/// Selects a job for the given machine based on the least slack algorithm.
std::optional<std::shared_ptr<Job>>
Scheduler::SelectJobForMachine(unsigned long aMachineId) {
  std::vector<std::tuple<std::shared_ptr<Job>, unsigned long>> jobCadidates =
      {};
  std::vector<std::tuple<std::shared_ptr<Job>, unsigned long>>::iterator
      selectedJobCandidate = jobCadidates.end();

  // Fills the vector with job candidates.
  std::for_each(
      mJobs.begin(), mJobs.end(),
      [&jobCadidates, aMachineId](std::shared_ptr<Job> &aJob) -> void {
        if (aJob->GetTasks().empty())
          return;

        std::shared_ptr<Task> &task = aJob->GetTasks().front();

        if (task->GetMachineId() != aMachineId)
          return;

        jobCadidates.emplace_back(aJob, aJob->ComputeTaskDurationSum());
      });

  // Gets the iterator to job with the longest duration.
  selectedJobCandidate = std::max_element(
      jobCadidates.begin(), jobCadidates.end(),
      [](const std::tuple<std::shared_ptr<Job>, unsigned long> &aLHS,
         const std::tuple<std::shared_ptr<Job>, unsigned long> &aRHS) -> bool {
        return std::get<1>(aLHS) < std::get<1>(aRHS);
      });

  // If there is no job with the longest duration return a nullopt.
  if (selectedJobCandidate == jobCadidates.end()) {
    return std::nullopt;
  }

  // Returns the selected job candidate.
  return std::get<0>(*selectedJobCandidate);
}

void Scheduler::Schedule() {
  std::vector<std::shared_ptr<Machine>> freeMachines = {};

  freeMachines.reserve(mMachines.size());

  while (true) {
    std::optional<unsigned long> deltaTime = std::nullopt;

    // Frees the free machines (lol).
    freeMachines.clear();

    // Stops all the tasks that have finished, and create the vector of tasks
    //  that can receive new tasks.
    std::for_each(
        mMachines.begin(), mMachines.end(),
        [this, &freeMachines](
            const std::pair<unsigned long, std::shared_ptr<Machine>> &aPair) {
          const std::shared_ptr<Machine> &machine = std::get<1>(aPair);

          // If the machine does not have a current task, it's free anyways, so
          // add it to the vector of free machines.
          if (not machine->HasActiveTask()) {
            freeMachines.push_back(machine);
            return;
          }

          // Get the active task of the machine and check if it's expired, if it
          // is not, just return and continue to the next machine.
          if (this->mCurrentTime < machine->GetActiveTask()->GetStartTime() +
                                       machine->GetActiveTask()->GetDuration())
            return;

          // Stops the task.
          machine->GetActiveTask()->SetEndTime(mCurrentTime);
          machine->DeleteActiveTask();

          // Adds the machine to the free machines.
          freeMachines.push_back(machine);
        });

    // Starts all the tasks if needed.
    std::for_each(freeMachines.begin(), freeMachines.end(),
                  [&deltaTime, this](const std::shared_ptr<Machine> &aMachine) {
                    // Gets the job that should be executed for the machine.
                    //  If no job could be found just return and continue to the
                    //  next machine.
                    std::optional<std::shared_ptr<Job>> optionalJob =
                        this->SelectJobForMachine(aMachine->GetId());
                    if (not optionalJob.has_value())
                      return;
                    std::shared_ptr<Job> &job = *optionalJob;

                    // Gets the task that should be executed.
                    std::shared_ptr<Task> task = job->GetTasks().front();
                    job->GetTasks().pop_front();

                    // Starts the task.
                    task->SetStartTime(mCurrentTime);
                    aMachine->SetActiveTask(task);

                    // If the delta time is not set, then set it to the duration
                    // of the task,
                    //  else set it to the max of the two.
                    if (deltaTime == std::nullopt)
                      deltaTime = task->GetDuration();
                    else
                      deltaTime = std::max(*deltaTime, task->GetDuration());
                  });

    // If the delta time is null, we know that no tasks have been performed, so
    // nothing has been enqueued.
    if (deltaTime == std::nullopt)
      break;

    // Adds the delta time to the current time.
    mCurrentTime += *deltaTime;
  }
}
