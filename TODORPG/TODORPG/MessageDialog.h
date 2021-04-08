#pragma once
#include <wx/wx.h>

class MessageDialog : public wxDialog
{
public:
	MessageDialog(const wxString& title, const std::string message);
private:
	wxStaticText* messageST = nullptr;
	wxButton* okButton = nullptr;
	void onClickedOK(wxCommandEvent& event);
};

