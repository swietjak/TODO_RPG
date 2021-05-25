#include "UsersList.h"
#include <tchar.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <Windows.h>
#include <debugapi.h>

UsersList::UsersList(const char* filename)
{
	std::ifstream f(filename);
	f >> this->j;
	this->json_text = j.dump().c_str();
	for (auto object : j)
	{
		auto tasks = this->FetchTasks(object["tasks"]);
		auto cycleTasks = this->FetchCycleTasks(object["cycle_tasks"]);
		List.push_back(new User(object["username"], object["password"], object["experience"], tasks, cycleTasks));
	}
}

UsersList::UsersList()
{
	std::multimap<std::string, int, int> chuj;
}

UsersList::~UsersList()
{
	for (auto &usr : this->List)
	{
		delete usr;
		usr = nullptr;
	}
}

std::vector<Task*> UsersList::FetchTasks(json tasks)
{
	std::vector<Task*> res;
	for (auto task : tasks)
	{
		res.push_back(new Task(task["id"], task["title"], task["description"], task["created_at"], task["expiration_time"], ReturnEnumFromJson(task["difficulty"])));
	}
	return res;
}

std::vector<CycleTask*> UsersList::FetchCycleTasks(json tasks)
{
	std::vector<CycleTask*> res;
	for (auto task : tasks)
	{
		res.push_back(new CycleTask(task["id"], task["title"], task["description"], task["created_at"], task["expiration_time"], ReturnEnumFromJson(task["difficulty"]), task["times_used"]));
	}
	return res;
}

User* UsersList::FindAndVerifyUser(const char* username, const char* password)
{
	auto user = this->FindUser(username);
	if(!user)
		throw "No such user. Try Again.";
	if (user->ValidatePassword(password))
		return user;
	else
		throw "Wrong password. Try Again.";
}

User* UsersList::FindUser(const char* username)
{
	for (auto user : List)
	{
		if (user->username.compare(username) == 0)
		{
			return user;
		}
	}
	return nullptr;
}

void UsersList::AddUser(User* usr)
{
	this->List.push_back(usr);
	this->j.push_back(usr->ReturnUserJson());
	this->UpdateJson();
}

void UsersList::RemoveTask(const char* username, int _id)
{
	this->FindUser(username)->RemoveTask(_id);
	this->UpdateJson();
}

void UsersList::UpdateJson()
{
	std::ofstream f("data.json", std::ios_base::out);
	j.clear();
	for (auto user : this->List)
		j.push_back(user->ReturnUserJson());
	f << std::setw(4) << j;
}

std::multimap<std::string, std::pair<int, int>> UsersList::GetUsersStats()
{
	std::multimap<std::string, std::pair<int, int>> mp;
	for (auto u : this->List)
	{
		mp.insert(std::make_pair(u->username, std::pair<int, int>(u->GetLevel(), u->GetExperience())));
	}
	return mp;
}

TaskDifficulty UsersList::ReturnEnumFromJson(std::string difficulty)
{
	if (difficulty == "easy")
	{
		return TaskDifficulty::Easy;
	}
	else if(difficulty == "medium")
	{
		return TaskDifficulty::Medium;
	}
	else 
	{
		return TaskDifficulty::Hard;
	}
}