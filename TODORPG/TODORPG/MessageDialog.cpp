#include "MessageDialog.h"


MessageDialog::MessageDialog(const wxString& title, const std::string message) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(310, 210))
{
	auto panel = new wxPanel(this);
	auto vbox = new wxBoxSizer(wxVERTICAL);
	auto vbox2 = new wxBoxSizer(wxVERTICAL);
	auto hbox = new wxBoxSizer(wxHORIZONTAL);
	auto hbox2 = new wxBoxSizer(wxHORIZONTAL);
	this->messageST = new wxStaticText(panel, wxID_ANY, message);
	this->okButton = new wxButton(panel, wxID_ANY, "OK");
	vbox->AddStretchSpacer(1);
	vbox->Add(this->messageST, wxSizerFlags().CenterHorizontal()); //wxSizerFlags().CenterHorizontal() 0, wxEXPAND, 0
	vbox->AddStretchSpacer(1);
	vbox->Add(this->okButton, wxSizerFlags().CenterHorizontal());
	//vbox2->Add(vbox, wxSizerFlags().Expand());
	hbox->AddStretchSpacer(1);
	hbox->Add(vbox, wxSizerFlags().CenterVertical());
	hbox->AddStretchSpacer(1);
	//hbox2->Add(hbox, wxSizerFlags().Expand());
	/**/
	

	panel->SetSizer(hbox);

	//panel2->SetSizer(hbox);
}