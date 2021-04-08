#include "Task.h"

Task::Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskExpirationDate, TaskDifficulty _td):Task(_id, _taskTitle, _taskDescription, time(0), _taskExpirationDate, _td)
{
}

Task::Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskCreatedAt, std::time_t _taskExpirationDate, TaskDifficulty _td)
{
	this->id = _id;
	this->taskTitle = _taskTitle;
	this->taskDescription = _taskDescription;
	this->taskCreatedAt = _taskCreatedAt;
	this->taskExpirationDate = _taskExpirationDate;
	this->td = _td;
}

void Task::SetCreatedAt(time_t t)
{
	this->taskCreatedAt = t;
}

int Task::GetId()
{
	return this->id;
}
std::string Task::GetTitle()
{
	return this->taskTitle;
}
std::string Task::GetDescription()
{
	return this->taskDescription;
}
std::time_t Task::GetCreatedAt()
{
	return this->taskCreatedAt;
}
std::time_t Task::GetExpirationDate()
{
	return this->taskExpirationDate;
}
TaskDifficulty Task::GetTaskDifficulty()
{
	return this->td;
}

void Task::SetId(int _id)
{
	this->id = _id;
}

void Task::SetExpirationDate(time_t t)
{
	this->taskExpirationDate = t;
}

json Task::ReturnTaskJson()
{
	json res = { {"id", id},
		{"title", taskTitle},
		{"description", taskDescription},
		{"difficulty", GetDifficultyFromEnum()},
		{"created_at", taskCreatedAt},
		{"expiration_time", taskExpirationDate} };
	return res;
}

std::string Task::GetDifficultyFromEnum()
{
	switch (td)
	{
	case TaskDifficulty::Easy:
		return "easy";
	case TaskDifficulty::Medium:
		return "medium";
	case TaskDifficulty::Hard:
		return "hard";
	default:
		return "easy";
	}
}

Task::~Task() {

}