/*@file*/
#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <chrono>
#include <ctime>
#include "User.h"

/**
* Klasa inplementująca okno dialogowe do wprowadzania zadań. Dziedziczy publicznie po klasie wxDialog.
*/
class TaskInputDialog : public wxDialog
{
public:
	/**
	* Konstruktor wieloargumentowy klasy TaskInputDialog
	* @param title tytuł okna
	* @param _user obiekt klasy użytkownika
	*/
	TaskInputDialog(const wxString& title, User* _user);
	wxStaticText* titleST = nullptr; //< tekst statyczny opisujący pole do wprowadzania tytułu
	wxStaticText* descriptionST = nullptr;//< tekst statyczny opisujący pole do wprowadzania opisu
	wxStaticText* dateST = nullptr; //< tekst statyczny opisujący pole do wprowadzania daty
	wxStaticText* timeST = nullptr; //< tekst statyczny opisujący pole do wprowadzania godziny
	wxStaticText* difficultyST = nullptr; //< tekst statyczny opisujący pole do wprowadzania poziomu trudności
	wxButton* submitButton = nullptr; //< przycisk do zatwierdzenia wprowadzenia zadania
	wxTextCtrl* titleInput = nullptr; //< pole do wprowadzania tytułu
	wxTextCtrl* descriptionInput = nullptr; //< pole do wprowadzania opisu
	wxDatePickerCtrl* expirationDateInput = nullptr; //< pole do wprowadzania daty
	wxTimePickerCtrl* expirationTimeInput = nullptr; //< pole do wprowadzania godziny
	wxChoice* difficultyInput = nullptr; //< pole do wprowadzania poziomu trudności
	wxCheckBox* isCycle = nullptr; //< checkbox do zatwierdzenia czy zadanie ma być cykliczne
	User* user = nullptr; //< użytkownik do którego dodajemy zadanie
	wxStaticText* errorST = nullptr; //< tekst statyczny wyświetlający błąd związany z błędnym wprowadzeniem danych
private:
	void onClickSubmit(wxCommandEvent& event); //< funkcja obsługująca dodanie zadania
	wxBoxSizer* verticalSizer = nullptr;
	void OnQuit(wxCloseEvent& event); //< funkcja obsługująca kliknięcie krzyżyka
	wxArrayString strArr;
	void InitStrArr();
	void DisplayLayout();
};