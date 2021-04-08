#include "User.h"

User::User() : username(""), password(""), experience(1)
{
}

User::~User()
{
	for (auto task : this->userTasks)
	{
		delete task;
		task = nullptr;
	}
	for (auto task : this->userCycleTasks)
	{
		delete task;
		task = nullptr;
	}

}

int User::GetMaxId()
{
	int maximum = 0;
	for (auto t : this->userTasks)
	{
		if (maximum < t->GetId())
		{
			maximum = t->GetId();
		}
	}

	for (auto t : this->userCycleTasks)
	{
		if (maximum < t->GetId())
		{
			maximum = t->GetId();
		}
	}
	return maximum;
}

void User::AddTask(Task* t)
{
	int max_id = this->GetMaxId();
	t->SetId(++max_id);
	this->userTasks.push_back(t);
}

void User::AddTask(Task* t, time_t timeToSet)
{
	t->SetCreatedAt(timeToSet);
	t->SetExpirationDate(timeToSet + DAY);
	this->AddTask(t);
}

void User::AddCycleTask(CycleTask* t)
{
	int max_id = this->GetMaxId();
	t->SetId(++max_id);
	this->userCycleTasks.push_back(t);
	this->userTasks.push_back(new Task(*static_cast<Task*>(t)));
}

Task* User::FindTask(int _id)
{
	for (auto t : userTasks)
	{
		if (_id == t->GetId())
			return t;
	}

	return nullptr;
}

void User::RemoveTask(int _id)
{
	for (auto it = this->userTasks.begin(); it != this->userTasks.end(); it++)
	{
		if ((*it)->GetId() == _id)
		{
			this->UpdateExperience((*it)->GetTaskDifficulty(), (*it)->GetExpirationDate());
			this->userTasks.erase(it);
			break;
		}
	}
}

void User::RemoveCycleTask(int _id)
{
	for (auto it = this->userCycleTasks.begin(); it != this->userCycleTasks.end(); it++)
	{
		if ((*it)->GetId() == _id)
		{
			this->userCycleTasks.erase(it);
			break;
		}
	}
}

void User::UpdateExperience(TaskDifficulty td, time_t _expDate)
{
	this->experience += (static_cast<int>(td) + 1) * (_expDate > time(0));
}

User::User(std::string _username, std::string _password, int _experience, std::vector<Task*> _userTasks, std::vector<CycleTask*> _userCycleTasks)
{
	this->username = _username;
	this->password = _password;
	this->experience = _experience;
	this->userTasks = _userTasks;
	this->userCycleTasks = _userCycleTasks;
}

void User::CopyTasks(std::vector<Task*> otherTasks)
{
	for(auto task: otherTasks)
	{ }
}

bool User::ValidatePassword(const char* pwd)
{
	return this->password.compare(pwd) == 0;
}

Task* User::GetTask(int pos)
{
	return this->userTasks[pos];
}

int User::GetExperience()
{
	return this->experience;
}

int User::GetLevel()
{
	return floor((sqrt(this->experience)/4) + 1);
}

int User::GetTasksNumber()
{
	return this->userTasks.size();
}

json User::ReturnUserJson()
{
	json res = { {"username", username}, {"password", password}, {"experience", experience} };
	json arr = json::array();
	json cycleArr = json::array();
	for (auto task : userTasks)
	{
		arr.push_back(task->ReturnTaskJson());
	}
	for (auto task : userCycleTasks)
	{
		cycleArr.push_back(task->ReturnCycleTaskJson());
	}
	res["tasks"] = arr;
	res["cycle_tasks"] = cycleArr;
	return res;
}