#include "TaskInputDialog.h"

TaskInputDialog::TaskInputDialog(const wxString& title, User* _user) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(500, 430))
{
	InitStrArr();

	this->user = _user;

	this->DisplayLayout();

	this->submitButton->Bind(wxEVT_BUTTON, &TaskInputDialog::onClickSubmit, this);
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(TaskInputDialog::OnQuit));
}

void TaskInputDialog::OnQuit(wxCloseEvent& event)
{
	EndModal(wxID_CANCEL);
	this->Destroy();
}

void TaskInputDialog::onClickSubmit(wxCommandEvent& event)
{
	if (titleInput->GetValue().ToStdString()._Equal(""))
		this->errorST->SetLabelText("Title is empty");
	else if (descriptionInput->GetValue().ToStdString()._Equal(""))
		this->errorST->SetLabelText("Description is empty");
	else if (this->difficultyInput->GetSelection() == -1)
		this->errorST->SetLabelText("Difficulty is empty");
	else
	{
		OutputDebugStringA(titleInput->GetValue().ToStdString().c_str());
		OutputDebugStringA(titleInput->GetValue().ToStdString().c_str());
		auto currDay = wxDateTime(time(0)).GetTicks();
		TaskDifficulty diff = static_cast<TaskDifficulty>(this->difficultyInput->GetSelection());
		time_t exp_time = expirationDateInput->GetValue().GetTicks() + expirationTimeInput->GetValue().GetTicks() - currDay;

		if (isCycle && isCycle->GetValue())
			this->user->AddCycleTask(new CycleTask(0, titleInput->GetValue().ToStdString(), descriptionInput->GetValue().ToStdString(), exp_time, diff));
		else
			this->user->AddTask(new Task(0, titleInput->GetValue().ToStdString(), descriptionInput->GetValue().ToStdString(), exp_time, diff));

		SetReturnCode(wxID_OK);
		this->Destroy();
	}
}

void TaskInputDialog::InitStrArr()
{
	this->strArr.Add("easy");
	this->strArr.Add("medium");
	this->strArr.Add("hard");
}

void TaskInputDialog::DisplayLayout()
{
	verticalSizer = new wxBoxSizer(wxVERTICAL);

	this->titleST = new wxStaticText(this, wxID_ANY, "title", wxPoint(10, 11), wxSize(200, 18));
	this->titleInput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 30), wxSize(300, 30));
	verticalSizer->Add(titleST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(titleInput, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->descriptionST = new wxStaticText(this, wxID_ANY, "description", wxPoint(10, 66), wxSize(200, 18));
	this->descriptionInput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 85), wxSize(300, 30));
	verticalSizer->Add(descriptionST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(descriptionInput, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->dateST = new wxStaticText(this, wxID_ANY, "date of completion", wxPoint(10, 121), wxSize(200, 18));
	this->expirationDateInput = new wxDatePickerCtrl(this, wxID_ANY, wxDateTime(time(0)), wxPoint(10, 140), wxSize(300, 30));
	verticalSizer->Add(dateST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(expirationDateInput, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->timeST = new wxStaticText(this, wxID_ANY, "time of completion", wxPoint(10, 176), wxSize(200, 18));
	this->expirationTimeInput = new wxTimePickerCtrl(this, wxID_ANY, wxDateTime(time(0)), wxPoint(10, 195), wxSize(300, 30));
	verticalSizer->Add(timeST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(expirationTimeInput, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->difficultyST = new wxStaticText(this, wxID_ANY, "difficulty", wxPoint(10, 231), wxSize(200, 18));
	this->difficultyInput = new wxChoice(this, wxID_ANY, wxPoint(10, 250), wxSize(100, 30), this->strArr);
	verticalSizer->Add(difficultyST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(difficultyInput, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->isCycle = user->GetLevel() > 2 ? new wxCheckBox(this, wxID_ANY, "Make it cycle", wxPoint(10, 290)) : nullptr;
	verticalSizer->Add(isCycle, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->errorST = new wxStaticText(this, wxID_ANY, "", wxPoint(10, 310), wxSize(200, 18));
	verticalSizer->Add(errorST, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->submitButton = new wxButton(this, wxID_ANY, "submit", wxPoint(10, 340), wxSize(150, 50));
	verticalSizer->Add(submitButton, 0, wxALIGN_LEFT | wxLEFT, 30);
	verticalSizer->Add(-1, 5);

	this->SetSizer(verticalSizer);
}