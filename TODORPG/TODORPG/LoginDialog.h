#pragma once
#include <wx/wx.h>
#include "json.hpp"
#include "UsersList.h"

class LoginDialog : public wxDialog
{
public:
	LoginDialog(const wxString& title, UsersList* ul);
	wxButton* submitButton = nullptr;
	wxButton* cancelButton = nullptr;
	wxTextCtrl* usernameInput = nullptr;
	wxTextCtrl* passwordInput = nullptr;
	wxStaticText* usernameST = nullptr;
	wxStaticText* passwordST = nullptr;
	wxStaticText* errorST = nullptr;
	wxString name = "";
	bool loginClicked = false;
	UsersList* usersList;
	User* GetResult();
private:
	void onClickLoginFunction(wxCommandEvent& event);
	void onClickCancelFunction(wxCommandEvent& event);
	void DisplayLayout();
	User* response;
};

