#pragma once
#include "Task.h"
class CycleTask :
    public Task
{
public:
    CycleTask(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskCreatedAt, std::time_t _taskExpirationDate, TaskDifficulty _td, int _timesUsed);
    CycleTask(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskExpirationDate, TaskDifficulty _td);
    void IncrementTimesUsed();
    int GetTimesUsed();
    virtual json ReturnCycleTaskJson();
private:
    int timesUsed;
};

