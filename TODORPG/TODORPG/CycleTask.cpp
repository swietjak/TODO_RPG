#include "CycleTask.h"

CycleTask::CycleTask(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskCreatedAt, std::time_t _taskExpirationDate, TaskDifficulty _td, int _timesUsed) : Task(_id, _taskTitle, _taskDescription, _taskCreatedAt, _taskExpirationDate, _td)
{
	this->timesUsed = _timesUsed;
}

CycleTask::CycleTask(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskExpirationDate, TaskDifficulty _td) : CycleTask(_id, _taskTitle, _taskDescription, time(0), _taskExpirationDate, _td, 1)
{
}

void CycleTask::IncrementTimesUsed()
{
	this->timesUsed++;
}

int CycleTask::GetTimesUsed()
{
	return this->timesUsed;
}

json CycleTask::ReturnCycleTaskJson()
{
	json res = this->ReturnTaskJson();
	res["times_used"] = this->timesUsed;
	return res;
}