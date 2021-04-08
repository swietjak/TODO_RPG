#pragma once
#include <string>
#include <ctime>
#include "json.hpp"
#include "TaskDifficulty.h"
#define DAY (24*60*60*1.0)

using json = nlohmann::json;

class Task
{
public:
	Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskCreatedAt, std::time_t _taskExpirationDate, TaskDifficulty _td);
	Task(int _id, std::string _taskTitle, std::string _taskDescription, std::time_t _taskExpirationDate, TaskDifficulty _td);
	~Task();
	int GetId();
	std::string GetTitle();
	std::string GetDescription();
	std::time_t GetCreatedAt();
	std::time_t GetExpirationDate();
	TaskDifficulty GetTaskDifficulty();
	virtual json ReturnTaskJson();
	void SetId(int _id);
	void SetCreatedAt(time_t t);
	void SetExpirationDate(time_t t);
private:
	int id;
	std::string taskTitle;
	std::string taskDescription;
	std::string GetDifficultyFromEnum();
	std::time_t taskCreatedAt;
	std::time_t taskExpirationDate;
	std::time_t taskExpirationTime;
	TaskDifficulty td;
};

