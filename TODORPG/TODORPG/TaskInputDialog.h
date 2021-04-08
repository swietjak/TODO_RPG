#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <chrono>
#include <ctime>
#include "User.h"

class TaskInputDialog : public wxDialog
{
public:
	TaskInputDialog(const wxString& title, User* _user);
	wxStaticText* titleST = nullptr;
	wxStaticText* descriptionST = nullptr;
	wxStaticText* dateST = nullptr;
	wxStaticText* timeST = nullptr;
	wxStaticText* difficultyST = nullptr;
	wxButton* submitButton = nullptr;
	wxTextCtrl* titleInput = nullptr;
	wxTextCtrl* descriptionInput = nullptr;
	wxDatePickerCtrl* expirationDateInput = nullptr;
	wxTimePickerCtrl* expirationTimeInput = nullptr;
	wxChoice* difficultyInput = nullptr;
	wxCheckBox* isCycle = nullptr;
	User* user = nullptr;
	void onClickSubmit(wxCommandEvent& event);
	wxStaticText* errorST = nullptr;
private:
	wxArrayString strArr;
	void InitStrArr();
	void DisplayLayout();
};

