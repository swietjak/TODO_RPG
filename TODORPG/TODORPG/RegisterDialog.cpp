#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(const wxString& title, UsersList* ul) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(300, 330))
{
    this->DisplayLayout();
    this->usersList = ul;
}

void RegisterDialog::DisplayLayout()
{
    credentialsSizer = new wxBoxSizer(wxVERTICAL);
    allSizer = new wxBoxSizer(wxVERTICAL);
    buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

    this->usernameST = new wxStaticText(this, wxID_ANY, wxT("username"), wxPoint(30, 22), wxSize(200, 18));
    this->usernameInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 40), wxSize(200, 30));
    credentialsSizer->Add(usernameST, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(usernameInput, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(-1, 10);

    this->passwordST = new wxStaticText(this, wxID_ANY, wxT("password"), wxPoint(30, 75), wxSize(200, 18));
    this->passwordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 94), wxSize(200, 30), wxTE_PASSWORD);
    credentialsSizer->Add(passwordST, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(passwordInput, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(-1, 10);

    this->repeatPasswordST = new wxStaticText(this, wxID_ANY, wxT("repeat password"), wxPoint(30, 130), wxSize(200, 18));
    this->repeatPasswordInput = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(30, 150), wxSize(200, 30), wxTE_PASSWORD);
    credentialsSizer->Add(repeatPasswordST, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(repeatPasswordInput, 0, wxALIGN_LEFT | wxLEFT);
    credentialsSizer->Add(-1, 10);

    this->errorST = new wxStaticText(this, wxID_ANY, "", wxPoint(30, 190), wxSize(200, 36));

    this->submitButton = new wxButton(this, wxID_ANY, wxT("register"), wxPoint(50, 250), wxDefaultSize);
    this->cancelButton = new wxButton(this, wxID_ANY, wxT("cancel"), wxPoint(130, 250), wxDefaultSize);
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

    this->submitButton->Bind(wxEVT_BUTTON, &RegisterDialog::onClickRegister, this);
    this->cancelButton->Bind(wxEVT_BUTTON, &RegisterDialog::onClickCancel, this);
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(RegisterDialog::OnQuit));
}

void RegisterDialog::onClickRegister(wxCommandEvent& event)
{
    std::regex passwordPattern = std::regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[a-zA-Z]).{8,}$");
    if (this->usersList->FindUser(usernameInput->GetValue()))
    {
        this->errorST->SetLabelText("Such user already exists. Pick another name.");
    }
    else if (usernameInput->GetValue().ToStdString() == "")
    {
        this->errorST->SetLabelText("Username is empty");
    }
    else if (passwordInput->GetValue().ToStdString() == "")
    {
        this->errorST->SetLabelText("Password is empty");
    }
    else if (!this->VerifyPassword(passwordInput->GetValue().ToStdString()))
    {
        return;
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

bool RegisterDialog::VerifyPassword(std::string pwd)
{
    if (pwd.length() < 8)
    {
        this->errorST->SetLabelText("Password must be at least 8 characters long");
        return false;
    }

    std::regex lowercasePattern = std::regex("^(?=.*[a-z]).{1,}$");
    std::regex uppercasePattern = std::regex("^(?=.*[A-Z]).{1,}$");
    std::regex digitPattern = std::regex("^(?=.*[\\d]).{1,}$");
    if (!std::regex_match(pwd, lowercasePattern))
    {
        this->errorST->SetLabelText("No lowercase character in password");
        return false;
    }
    if (!std::regex_match(pwd, uppercasePattern))
    {
        this->errorST->SetLabelText("No uppercase character in password");
        return false;
    }
    if (!std::regex_match(pwd, digitPattern))
    {
        this->errorST->SetLabelText("No digit in password");
        return false;
    }
    return true;
}

void RegisterDialog::onClickCancel(wxCommandEvent& event) {
    this->Destroy();
}

void RegisterDialog::OnQuit(wxCloseEvent& event)
{
    this->Destroy();
}
