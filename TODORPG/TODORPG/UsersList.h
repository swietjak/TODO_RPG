#pragma once
#include <vector>
#include "User.h"
#include <fstream>

using json = nlohmann::json;

class UsersList
{
public:
	UsersList();
	~UsersList();
	UsersList(const char* filename);
	User* FindAndVerifyUser(const char* username, const char* password);
	User* FindUser(const char* username);
	void AddUser(User* usr);
	void RemoveTask(const char* username, int _id);
	std::string json_text;
	void UpdateJson();
private:
	json j;
	std::vector<User*> List;
	std::vector<Task*> FetchTasks(json tasks);
	std::vector<CycleTask*> FetchCycleTasks(json tasks);
	TaskDifficulty ReturnEnumFromJson(std::string difficulty);
};

