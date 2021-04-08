#pragma once
#include <wx/wx.h>
#include "UsersList.h"

class RegisterDialog : public wxDialog
{
public:
	RegisterDialog(const wxString& title, UsersList* ul);
	wxButton* submitButton = nullptr;
	wxButton* cancelButton = nullptr;
	wxTextCtrl* usernameInput = nullptr;
	wxTextCtrl* passwordInput = nullptr;
	wxTextCtrl* repeatPasswordInput = nullptr;
	wxStaticText* usernameST = nullptr;
	wxStaticText* passwordST = nullptr;
	wxStaticText* repeatPasswordST = nullptr;
	wxStaticText* errorST = nullptr;
	wxString name = "";
	bool loginClicked = false;
	UsersList* usersList;
	//User GetResult();
private:
	void onClickRegister(wxCommandEvent& event);
	void onClickCancel(wxCommandEvent& event);
	void DisplayLayout();
	//User response;
};

