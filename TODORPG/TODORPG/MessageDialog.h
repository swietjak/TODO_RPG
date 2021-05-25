/*@file*/
#pragma once
#include <wx/wx.h>

/**
* Klasa inplementująca okno dialogowe do wyświetlania powiadomienia. Dziedziczy publicznie po klasie wxDialog.
*/
class MessageDialog : public wxDialog
{
public:
	/**
	* Konstruktor wieloargumentowy klasy MessageDialog
	* @param title tytuł okna
	* @param message wiadomość do wypisania w oknie
	*/
	MessageDialog(const wxString& title, const std::string message);
	~MessageDialog();
private:
	wxStaticText* messageST = nullptr; //< pole do wypisania wiadomości
	wxButton* okButton = nullptr;
	wxPanel* panel = nullptr;
	wxBoxSizer* vbox = nullptr;
	wxBoxSizer* vbox2 = nullptr;
	wxBoxSizer* hbox = nullptr;
	wxBoxSizer* hbox2 = nullptr;
	void OnQuit(wxCloseEvent& event);
	void onClickedOK(wxCommandEvent& event);
};

