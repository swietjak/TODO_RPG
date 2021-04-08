#include "LoginDialog.h"

LoginDialog::LoginDialog(const wxString& title, UsersList* ul) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(300, 230)) 
{
    this->DisplayLayout();
    this->usersList = ul;
    OutputDebugStringA(ul->json_text.c_str());
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
    Destroy();
}

User* LoginDialog::GetResult()
{
    return this->response;
}

void LoginDialog::DisplayLayout()
{
    this->usernameST = new wxStaticText(this, wxID_ANY, wxT("login"), wxPoint(30, 22), wxSize(200, 18));
    this->usernameInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 40), wxSize(200, 30));
    this->passwordST = new wxStaticText(this, wxID_ANY, wxT("haslo"), wxPoint(30, 75), wxSize(200, 18));
    this->passwordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 94), wxSize(200, 30), wxTE_PASSWORD);
    this->submitButton = new wxButton(this, wxID_ANY, wxT("zaloguj sie"), wxPoint(50, 170), wxDefaultSize);
    this->cancelButton = new wxButton(this, wxID_ANY, wxT("anuluj"), wxPoint(130, 170), wxDefaultSize);
    this->errorST = new wxStaticText(this, wxID_ANY, "", wxPoint(30, 130), wxSize(200, 18));
    this->submitButton->Bind(wxEVT_BUTTON, &LoginDialog::onClickLoginFunction, this);
    this->cancelButton->Bind(wxEVT_BUTTON, &LoginDialog::onClickCancelFunction, this);

    Centre();
}