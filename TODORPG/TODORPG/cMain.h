/*@file*/
#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <wx/listctrl.h>
#include <chrono>
#include <ctime>
#include <string>
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "TaskInputDialog.h"
#include "MessageDialog.h"
#include "CycleTaskDialog.h"


class TaskDisplay;

/**
* Klasa inplementująca główne okno programu. Dziedziczy publicznie po klasie wxFrame.
*/
class cMain : public wxFrame
{
public:
	/**
	* Konstruktor bezargumentowy klasy cMain
	*/
	cMain();
	~cMain();
	wxButton* loginButton = nullptr;
	wxButton* registerButton = nullptr;
	wxButton* addTaskButton = nullptr;
	wxButton* logoutButton = nullptr;
	wxButton* cycleTasksButton = nullptr;
	User* currentUser = nullptr;
	void ChangeDisplayAfterLogin();
	void UpdateTaskDisp();
	void UpdateLevel();
	UsersList* ul = nullptr;
private:
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnRegisterButtonClicked(wxCommandEvent& evt);
	void OnCyckleTaskClicked(wxCommandEvent& evt);
	void onClickAddTaskFunction(wxCommandEvent& event);
	void onClickLogoutFunction(wxCommandEvent& event);
	void ChangeDisplayAfterLogout();
	void DisplayTasks();
	void HideTasks();
	void InitSizer();
	void ClearSizers();
	wxListView* listView = nullptr;
	wxStaticText* usernameST = nullptr;
	wxStaticText* levelST = nullptr;
	wxBoxSizer* allSizer = nullptr;
	wxBoxSizer* navSizer = nullptr;
	wxBoxSizer* tasksSizer = nullptr;
	wxBoxSizer* usrSizer = nullptr;
	wxBoxSizer* btnsSizer = nullptr;
	std::string ReturnUsernameMsg();
	std::string ReturnLevelMsg();
	std::vector<TaskDisplay*> tasksDisplays;
	const wxPoint taskStart = wxPoint(10, 60);
	void AppendLastTaskDisp();
	void AppendCycleTasks();
	void DisplayRanking();
};

/**
* Klasa inplementująca pole do wyświetlenia zadania cyklicznego. Dziedziczy publicznie po klasie wxPanel.
*/
class TaskDisplay : public wxPanel
{
public:
	/**
	* Konstruktor bezargumentowy klasy CyclTaskDisp. */
	TaskDisplay()
	{}
	/**
	* Konstruktor wieloargumentowy klasy CyclTaskDisp.
	* @param task zadanie które będzie wyświetlone
	* @param dialog okno dialogowe na którym będzie wyświetlane
	* @param placement umiejscowienie w oknie dialogowym
	*/
	TaskDisplay(Task* _task, wxPoint _placement, cMain* _frame);
	~TaskDisplay();
private:
	wxStaticText* titleST = nullptr;
	wxStaticText* descriptionST = nullptr;
	wxStaticText* dateST = nullptr;
	wxButton* doneBT = nullptr;
	wxButton* editBT = nullptr;
	void onClickDelete(wxCommandEvent& event); //< Funkcja obsługująca usunięcie zadania
	void SetColor(TaskDifficulty td);
	void InitSizers();
	int id;
	cMain* frame = nullptr;
	wxBoxSizer* upperInfoSizer = nullptr;
	wxBoxSizer* infoSizer = nullptr;
	wxBoxSizer* taskSizer = nullptr;
	//char* getTimeStr(time_t _time);
};
