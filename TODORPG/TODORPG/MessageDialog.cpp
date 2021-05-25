#include "MessageDialog.h"


MessageDialog::MessageDialog(const wxString& title, const std::string message) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(310, 210))
{
	this->panel = new wxPanel(this);
	this->vbox = new wxBoxSizer(wxVERTICAL);
	this->vbox2 = new wxBoxSizer(wxVERTICAL);
	this->hbox = new wxBoxSizer(wxHORIZONTAL);
	this->hbox2 = new wxBoxSizer(wxHORIZONTAL);
	this->messageST = new wxStaticText(panel, wxID_ANY, message);
	this->okButton = new wxButton(panel, wxID_ANY, "OK");
	vbox->AddStretchSpacer(1);
	vbox->Add(this->messageST, wxSizerFlags().CenterHorizontal()); //wxSizerFlags().CenterHorizontal() 0, wxEXPAND, 0
	vbox->AddStretchSpacer(1);
	vbox->Add(this->okButton, wxSizerFlags().CenterHorizontal());
	hbox->AddStretchSpacer(1);
	hbox->Add(vbox, wxSizerFlags().CenterVertical());
	hbox->AddStretchSpacer(1);

	
	this->okButton->Bind(wxEVT_BUTTON, &MessageDialog::onClickedOK, this);
	panel->SetSizer(hbox);
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MessageDialog::OnQuit));

}

void MessageDialog::OnQuit(wxCloseEvent& event)
{
	EndModal(wxID_OK);
	this->Destroy();
}

void MessageDialog::onClickedOK(wxCommandEvent& event)
{
	SetReturnCode(wxID_OK);
	this->Destroy();
}

MessageDialog::~MessageDialog()
{
	delete messageST;
	delete okButton;
	delete vbox2;
	delete hbox2;

	messageST = nullptr;
	okButton = nullptr;
	panel = nullptr;
	vbox = nullptr;
	vbox2 = nullptr;
	hbox = nullptr;
	hbox2 = nullptr;
}