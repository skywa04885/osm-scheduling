//
// Created by luke on 9/15/23.
//

#include "Scheduler.h"
#include "Job.h"
#include "Machine.h"
#include "Task.h"

#include <algorithm>
#include <iostream>
#include <tuple>

Scheduler::Scheduler(
    std::list<std::shared_ptr<Job>> aJobs,
    std::map<unsigned long, std::shared_ptr<Machine>> aMachines)
    : mJobs(aJobs), mMachines(aMachines), mCurrentTime(0UL) {}

/// Selects a job for the given machine based on the least slack algorithm.
std::optional<std::shared_ptr<Task>>
Scheduler::SelectTaskForMachine(unsigned long aMachineId) {
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

  // Gets the job candidate and the task, after which the task gets
  //  removed from the job.
  std::shared_ptr<Job> &job = std::get<0>(*selectedJobCandidate);
  std::shared_ptr<Task> task = job->GetTasks().front();
  job->GetTasks().pop_front();

  // Returns the task.
  return std::move(task);
}

/// Stops all the tasks if they're finished.
void Scheduler::StopFinishedTasks() {
  for (std::pair<unsigned long, std::shared_ptr<Machine>> pair : mMachines) {
    // Gets the machine and checks if it has an active task. If it does not,
    //  just ignore the machine.
    std::shared_ptr<Machine> &machine = std::get<1>(pair);
    if (not machine->HasActiveTask())
      continue;

    // Gets the machine's active task, if the task is not finished yet
    //  don't do anything.
    std::shared_ptr<Task> task = machine->GetActiveTask();
    if (this->mCurrentTime < task->GetEndTime())
      continue;

    // Deletes the active task from the machine.
    machine->DeleteActiveTask();

    // Gets the job and don't do anything if it still has tasks.
    std::shared_ptr<Job> job = task->GetJob().lock();
    if (job->HasTasks())
      continue;

    // Sets the end time of the job since there are no tasks remaining.
    job->SetEndTime(mCurrentTime);
  }
}

/// Starts tasks.
void Scheduler::StartTasks() {
  for (std::pair<unsigned long, std::shared_ptr<Machine>> pair : mMachines) {
    // Gets the machine.
    std::shared_ptr<Machine> machine = std::get<1>(pair);
    if (machine->HasActiveTask())
      continue;

    // Selects a task for the machine, if none could be found just continue.
    std::optional<std::shared_ptr<Task>> optionalTask =
        SelectTaskForMachine(machine->GetId());
    if (not optionalTask.has_value())
      continue;

    // Gets the task and the job it belongs to.
    std::shared_ptr<Task> task = *optionalTask;
    std::shared_ptr<Job> job = task->GetJob().lock();

    // Sets the starting time of the task and possibly the starting time
    //  of the job (if it's starting time has not been set yet).
    task->SetStartTime(mCurrentTime);
    if (not job->HasStartTime())
      job->SetStartTime(mCurrentTime);

    // Sets the task as the active task of the machine.
    machine->SetActiveTask(std::move(task));
  }
}

/// Gets the time of the nearest event.
std::optional<unsigned long> Scheduler::GetNearestEventTime() {
  std::optional<unsigned long> nearestEventTime = std::nullopt;

  for (std::pair<unsigned long, std::shared_ptr<Machine>> pair : mMachines) {
    // Gets the machine, if the machine does not have an active task just ignore
    // it.
    std::shared_ptr<Machine> machine = std::get<1>(pair);
    if (not machine->HasActiveTask())
      continue;

    // Gets the active task from the machine.
    std::shared_ptr<Task> task = machine->GetActiveTask();

    // Sets the nearest event time to the minimum of the existing nearest
    //  event time and the new event time.
    if (nearestEventTime.has_value())
      nearestEventTime = std::min(nearestEventTime.value(), task->GetEndTime());
    else
      nearestEventTime = task->GetEndTime();
  }

  return nearestEventTime;
}

void Scheduler::Schedule() {
  std::optional<unsigned long> nearestEventTime = 0UL;

  do {
    // Updates the current time.
    mCurrentTime = nearestEventTime.value();

    // Stops all the finished tasks.
    StopFinishedTasks();

    // Starts tasks.
    StartTasks();
  } while ((nearestEventTime = GetNearestEventTime()).has_value());
}
