#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <chrono>
#include <ctime>
#include <string>
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "TaskInputDialog.h"
#include "MessageDialog.h"
#define TASK_DISP_HEIGHT 45

class TaskDisplay;

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	wxButton* loginButton = nullptr;
	wxButton* registerButton = nullptr;
	wxButton* addTaskButton = nullptr;
	wxButton* logoutButton = nullptr;
	User* currentUser = nullptr;
	void ChangeDisplayAfterLogin();
	void UpdateTaskDisp();
	void UpdateLevel();
	UsersList* ul = nullptr;
private:
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void onClickAddTaskFunction(wxCommandEvent& event);
	void onClickLogoutFunction(wxCommandEvent& event);
	void ChangeDisplayAfterLogout();
	void DisplayTasks();
	void HideTasks();
	wxStaticText* usernameST = nullptr;
	wxStaticText* levelST = nullptr;
	std::string ReturnUsernameMsg();
	std::string ReturnLevelMsg();
	std::vector<TaskDisplay*> tasksDisplays;
	const wxPoint taskStart = wxPoint(10, 60);
	void AppendLastTaskDisp();
	void AppendCycleTasks();
	//void displayTasks();
};

class TaskDisplay
{
public:
	TaskDisplay()
	{}
	TaskDisplay(Task* _task, wxPoint _placement, cMain* _frame);
	~TaskDisplay();
private:
	wxStaticText* titleST = nullptr;
	wxStaticText* descriptionST = nullptr;
	wxStaticText* dateST = nullptr;
	wxButton* doneBT = nullptr;
	wxButton* editBT = nullptr;
	void onClickDelete(wxCommandEvent& event);
	int id;
	cMain* frame = nullptr;
	//char* getTimeStr(time_t _time);
};
