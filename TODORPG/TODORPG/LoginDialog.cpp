#include "LoginDialog.h"

LoginDialog::LoginDialog(const wxString& title, UsersList* ul) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(300, 230))
{
    this->DisplayLayout();
    this->usersList = ul;
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(LoginDialog::OnQuit));
}

void LoginDialog::onClickLoginFunction(wxCommandEvent& event) {
    try
    {
        this->response = this->usersList->FindAndVerifyUser(usernameInput->GetValue(), passwordInput->GetValue());
        if (IsModal())
        {
            EndModal(wxID_OK);
            Destroy();
        }
        else
        {
            SetReturnCode(wxID_OK);
            this->Show(false); // If modeless
        }
    }
    catch (const char* msg)
    {
        this->errorST->SetLabelText(msg);
    }
}

void LoginDialog::onClickCancelFunction(wxCommandEvent& event) {
    EndModal(wxID_CANCEL);
    Destroy();
}

User* LoginDialog::GetResult()
{
    return this->response;
}

void LoginDialog::OnQuit(wxCloseEvent& event)
{
    EndModal(wxID_CANCEL);
    this->Destroy();
}

void LoginDialog::DisplayLayout()
{
    credentialsSizer = new wxBoxSizer(wxVERTICAL);
    allSizer = new wxBoxSizer(wxVERTICAL);
    buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

    this->usernameST = new wxStaticText(this, wxID_ANY, wxT("login"));
    this->usernameInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(-1, -1), wxSize(200, 30));
    credentialsSizer->Add(usernameST, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(usernameInput, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(-1, 10);

    this->passwordST = new wxStaticText(this, wxID_ANY, wxT("haslo"), wxPoint(-1, -1), wxSize(200, 18));
    this->passwordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(-1, -1), wxSize(200, 30), wxTE_PASSWORD);
    credentialsSizer->Add(passwordST, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(passwordInput, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(-1, 10);

    this->submitButton = new wxButton(this, wxID_ANY, wxT("zaloguj sie"), wxPoint(50, 170), wxDefaultSize);
    this->cancelButton = new wxButton(this, wxID_ANY, wxT("anuluj"), wxPoint(130, 170), wxDefaultSize);
    this->errorST = new wxStaticText(this, wxID_ANY, "", wxPoint(30, 130), wxSize(200, 18));

    buttonsSizer->Add(submitButton, 0);
    buttonsSizer->Add(15, -1);
    buttonsSizer->Add(cancelButton, 0);

    allSizer->Add(-1, 5);
    allSizer->Add(credentialsSizer, 0, wxALIGN_CENTER_HORIZONTAL);
    allSizer->Add(-1, 5);
    allSizer->Add(errorST, 0, wxALIGN_CENTER_HORIZONTAL);
    allSizer->Add(-1, 5);
    allSizer->Add(buttonsSizer, 0, wxALIGN_CENTER_HORIZONTAL);
    this->SetSizer(allSizer);

    this->submitButton->Bind(wxEVT_BUTTON, &LoginDialog::onClickLoginFunction, this);
    this->cancelButton->Bind(wxEVT_BUTTON, &LoginDialog::onClickCancelFunction, this);
}