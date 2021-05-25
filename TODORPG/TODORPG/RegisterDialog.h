/*@file*/
#pragma once
#include <wx/wx.h>
#include <regex>
#include "UsersList.h"

/**
* Klasa inplementująca okno dialogowe do rejestracji nowego użytkownika. Dziedziczy publicznie po klasie wxDialog.
*/
class RegisterDialog : public wxDialog
{
public:
	/**
	* Konstruktor wieloargumentowy klasy RegisterDialog
	* @param title tytuł okna
	* @param ul obiekt klasy listy użytkowników
	*/
	RegisterDialog(const wxString& title, UsersList* ul);
	wxButton* submitButton = nullptr; //< przycisk do zatwierdzenia utworzenia nowego użytkownika
	wxButton* cancelButton = nullptr; //< przycisk do odrzucenia tworzenia nowego użytkownika
	wxTextCtrl* usernameInput = nullptr; //< pole do wprowadzania nazwy użytkownika
	wxTextCtrl* passwordInput = nullptr; //< pole do wprowadzania hasła
	wxTextCtrl* repeatPasswordInput = nullptr; //< pole do pootwierdzenia hasła
	wxStaticText* usernameST = nullptr; //< tekst statyczny opisujący pole do wprowadzania nazwę użytkownika
	wxStaticText* passwordST = nullptr; //< tekst statyczny opisujący pole do pootwierdzenia hasła
	wxStaticText* repeatPasswordST = nullptr; //< tekst statyczny opisujące pole do wprowadzania tytułu
	wxStaticText* errorST = nullptr; //< tekst statyczny wyświetlający błąd związany z błędnym wprowadzeniem danych
	UsersList* usersList; //< wskaźnik do listy użytkowników
	//User GetResult();
private:
	wxString name = "";
	bool loginClicked = false;
	void onClickRegister(wxCommandEvent& event);
	void onClickCancel(wxCommandEvent& event);
	void DisplayLayout();
	void OnQuit(wxCloseEvent& event);
	bool VerifyPassword(std::string pwd);
	wxBoxSizer* credentialsSizer = nullptr;
	wxBoxSizer* allSizer = nullptr;
	wxBoxSizer* buttonsSizer = nullptr;
	//User response;
};