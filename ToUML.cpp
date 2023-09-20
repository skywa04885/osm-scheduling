#include <algorithm>
#include <optional>
#include <set>
#include <vector>

#include "Job.h"
#include "Machine.h"
#include "Task.h"
#include "ToUML.h"

ToUML::ToUML(const std::string &aFileName)
    : mFileStream(aFileName, std::ios::out) {}

void ToUML::Render(
    const std::map<unsigned long, std::shared_ptr<Machine>> &aMachines,
    std::list<std::shared_ptr<Task>> aTasks) {
  mFileStream << "@startuml" << std::endl;
  mFileStream << "scale 10 as 90 pixels" << std::endl;

  // Creates all the machines.
  for (const std::pair<unsigned long, std::shared_ptr<Machine>> &pair :
       aMachines) {
    const std::shared_ptr<Machine> &machine = std::get<1>(pair);
    mFileStream << "concise \"Machine " << machine->GetId() << "\" as M"
                << machine->GetId() << std::endl;
  }

  // Shows all the tasks that are run.

  std::set<unsigned long, std::less<unsigned long>> set = {};
  set.insert(0);
  for (const std::shared_ptr<Task> &task : aTasks) {
    set.insert(task->GetEndTime());
  }

  for (unsigned long time   : set) {
    std::vector<std::shared_ptr<Task>> startedTasks = {};
    std::vector<std::shared_ptr<Task>> endedTasks = {};

    // Handles ending tasks.
    for (const std::shared_ptr<Task> &task : aTasks) {
      if (task->GetEndTime() != time)
        continue;

      endedTasks.push_back(task);
    }

    // Handles starting tasks.
    for (const std::shared_ptr<Task> &task : aTasks) {
      if (task->GetStartTime() != time)
        continue;

      startedTasks.push_back(task);
    }

    // Stuff
    if (not startedTasks.empty() || not endedTasks.empty())
      mFileStream << std::endl << "@" << time << std::endl;

    // Creates the ended task lines if needed.
    for (const std::shared_ptr<Task> &endedTask : endedTasks) {
      if (std::find_if(
              startedTasks.begin(), startedTasks.end(),
              [&endedTask](const std::shared_ptr<Task> &startedTask) -> bool {
                return endedTask->GetMachineId() == startedTask->GetMachineId();
              }) != startedTasks.end())
        continue;

      mFileStream << "M" << endedTask->GetMachineId() << " is {-}" << std::endl;
    }

    // Creates the started tasks stuff.
    for (const std::shared_ptr<Task> &startedTask : startedTasks) {
      std::shared_ptr<Job> job = startedTask->GetJob().lock();
      mFileStream << "M" << startedTask->GetMachineId() << " is \"Job "
                  << job->GetId() << ", Task" << startedTask->GetTaskNo()<< "\"" << std::endl;
    }
  }

  mFileStream << "@enduml" << std::endl;
}
