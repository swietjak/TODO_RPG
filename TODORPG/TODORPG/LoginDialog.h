/*@file*/
#pragma once
#include <wx/wx.h>
#include "json.hpp"
#include "UsersList.h"

/**
* Klasa inplementująca okno dialogowe do logowania. Dziedziczy publicznie po klasie wxDialog.
*/
class LoginDialog : public wxDialog
{
public:
    /**
    * Konstruktor wieloargumentowy klasy LoginDialog. Dziedziczy publicznie po klasie wxDialog.
    * @param title tytuł okna
    * @param ul obiekt klasy listy użytkowników
    */
    LoginDialog(const wxString& title, UsersList* ul);
    wxButton* submitButton = nullptr; //< przycisk do zatwierdzenia zalogowania
    wxButton* cancelButton = nullptr; //< przycisk do anulowania zalogowania
    wxTextCtrl* usernameInput = nullptr; //< pole do wprowadzania nazwy użytkownika
    wxTextCtrl* passwordInput = nullptr; //< pole do wprowadzania hasła
    wxStaticText* usernameST = nullptr; //< tekst statyczny opisujący pole do wprowadzania nazwę użytkownika
    wxStaticText* passwordST = nullptr; //< tekst statyczny opisujący pole do wprowadzania hasła
    wxStaticText* errorST = nullptr; //< tekst statyczny wyświetlający błąd związany z błędnym wprowadzeniem danych
    wxString name = "";
    bool loginClicked = false;
    UsersList* usersList;
    /**
    * returns obiekt zalogowanego użytkownika
    */
    User* GetResult();
private:
    void onClickLoginFunction(wxCommandEvent& event);
    void onClickCancelFunction(wxCommandEvent& event);
    void DisplayLayout();
    void OnQuit(wxCloseEvent& event);
    User* response;
    wxBoxSizer* credentialsSizer = nullptr;
    wxBoxSizer* allSizer = nullptr;
    wxBoxSizer* buttonsSizer = nullptr;
};




