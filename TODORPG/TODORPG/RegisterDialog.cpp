#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(const wxString& title, UsersList* ul) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(300, 330))
{
	this->DisplayLayout();
    this->usersList = ul;
}

void RegisterDialog::DisplayLayout()
{
    this->usernameST = new wxStaticText(this, wxID_ANY, wxT("username"), wxPoint(30, 22), wxSize(200, 18));
    this->usernameInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 40), wxSize(200, 30));
    
    this->passwordST = new wxStaticText(this, wxID_ANY, wxT("password"), wxPoint(30, 75), wxSize(200, 18));
    this->passwordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 94), wxSize(200, 30), wxTE_PASSWORD);
    
    this->repeatPasswordST = new wxStaticText(this, wxID_ANY, wxT("repeat password"), wxPoint(30, 130), wxSize(200, 18));
    this->repeatPasswordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 150), wxSize(200, 30), wxTE_PASSWORD);

    this->errorST = new wxStaticText(this, wxID_ANY, "", wxPoint(30, 190), wxSize(200, 18));

    this->submitButton = new wxButton(this, wxID_ANY, wxT("register"), wxPoint(50, 220), wxDefaultSize);
    this->cancelButton = new wxButton(this, wxID_ANY, wxT("cancel"), wxPoint(130, 220), wxDefaultSize);

    this->submitButton->Bind(wxEVT_BUTTON, &RegisterDialog::onClickRegister, this);
    this->cancelButton->Bind(wxEVT_BUTTON, &RegisterDialog::onClickCancel, this);
}

void RegisterDialog::onClickRegister(wxCommandEvent& event) {
    if (this->usersList->FindUser(usernameInput->GetValue()))
    {
        this->errorST->SetLabelText("Such user already exists. Pick another name.");
    }
    else if (strcmp(passwordInput->GetValue().c_str(), repeatPasswordInput->GetValue().c_str()))
    {
        this->errorST->SetLabelText("Passwords are not matching");
    }
    else
    {
        std::vector<Task*> emptyTasks;
        std::vector<CycleTask*> emptyCycleTasks;
        auto usr = new User(usernameInput->GetValue().ToStdString(), passwordInput->GetValue().ToStdString(), 1, emptyTasks, emptyCycleTasks);
        this->usersList->AddUser(usr);
        if (IsModal())
        {
            EndModal(wxID_OK);
        }
        else
        {
            SetReturnCode(wxID_OK);
            this->Show(false); // If modeless
        }
    }
    
}

void RegisterDialog::onClickCancel(wxCommandEvent& event) {
    this->Destroy();
}