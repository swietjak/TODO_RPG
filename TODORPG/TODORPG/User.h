#pragma once
#include <string>
#include "CycleTask.h"
#include <vector>
#include <cmath>

class User
{
public:
	User();
	~User();
	User(std::string _username, std::string _password, int _experience, std::vector<Task*> _userTasks, std::vector<CycleTask*> _userCycleTasks);
	std::string username;
	bool ValidatePassword(const char * pwd);
	void AddTask(Task* t);
	void AddTask(Task* t, time_t timeToSet);
	void AddCycleTask(CycleTask* t);
	void RemoveTask(int _id);
	void RemoveCycleTask(int _id);
	void UpdateExperience(TaskDifficulty td, time_t _expDate);
	Task* FindTask(int _id);
	int GetExperience();
	int GetLevel();
	int GetTasksNumber();
	Task* GetTask(int pos);
	json ReturnUserJson();
	std::vector<Task*> userTasks;
	std::vector<CycleTask*> userCycleTasks;
private:
	std::string password;
	int experience;
	int GetMaxId();
	int GetMaxIdCycle();
	void CopyTasks(std::vector<Task*> otherTasks);
};

