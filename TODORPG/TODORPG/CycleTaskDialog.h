/*@file*/
#pragma once
#include <wx/wx.h>
#include "User.h"
#define TASK_DISP_HEIGHT 45
#define WINDOW_WIDTH 440
#define HEIGHT_OFFSET 140
#define WINDOW_HEIGHT_USERLES 300

class CycleTaskDisp;

/**
* Klasa inplementująca okno dialogowe do wyświetlenia zadań cyklicznych. Dziedziczy publicznie po klasie wxDialog.
*/
class CycleTaskDialog : public wxDialog
{
public:
	/**
	* Konstruktor wieloargumentowy klasy CycleTaskDialog.
	* @param _user użytkownik którego zadania zostaną wyświetlone
	*/
	CycleTaskDialog(User* _user);
	~CycleTaskDialog();
	User* user = nullptr; //<obecny użytkownik
	/**
	* Funkcja uaktualnia zawartość okna
	*/
	void UpdateTaskDisp();
private:
	void ShowTasks();
	void HideTasks();
	void OnQuit(wxCloseEvent& event);
	const wxPoint taskStart = wxPoint(20, 10);
	wxBoxSizer* tasksSizer = nullptr;
	std::vector<CycleTaskDisp*> tasksDisplays;
};

/**
* Klasa inplementująca pole do wyświetlenia zadania cyklicznego. Dziedziczy publicznie po klasie wxPanel.
*/
class CycleTaskDisp : public wxPanel
{
public:
	/**
	* Konstruktor wieloargumentowy klasy CyclTaskDisp.
	* @param task zadanie które będzie wyświetlone
	* @param dialog okno dialogowe na którym będzie wyświetlane
	* @param placement umiejscowienie w oknie dialogowym
	* @param _id id pola
	*/
	CycleTaskDisp(CycleTask* task, CycleTaskDialog* dialog, wxPoint placement, int _id);
	~CycleTaskDisp();
	int id; //< id pola
private:
	Task* task = nullptr;
	CycleTaskDialog* frame = nullptr;
	wxStaticText* titleST = nullptr;
	wxStaticText* descriptionST = nullptr;
	wxButton* deleteBt = nullptr;
	wxBoxSizer* infoSizer = nullptr;
	wxBoxSizer* allSizer = nullptr;
	void OnDeleteClick(wxCommandEvent& evt);
	void SetColor();
};