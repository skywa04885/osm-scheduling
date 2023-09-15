//
// Created by luke on 9/15/23.
//

#ifndef BEROEPSPRODUCT_TASK_H
#define BEROEPSPRODUCT_TASK_H


class Task {
private:
    unsigned long mMachineId;
    unsigned long mDuration;
public:
    Task(unsigned long mMachineId, unsigned long mDuration) noexcept;
};


#endif //BEROEPSPRODUCT_TASK_H
