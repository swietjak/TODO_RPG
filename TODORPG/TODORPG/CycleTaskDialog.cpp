#include "CycleTaskDialog.h"

CycleTaskDialog::CycleTaskDialog(User* _user) : wxDialog(NULL, -1, "Cycle tasks", wxDefaultPosition, wxSize(500, 430))
{
	this->user = _user;
	this->ShowTasks();
	this->SetBackgroundColour(wxColour(200, 200, 200));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(CycleTaskDialog::OnQuit));
}

void CycleTaskDialog::OnQuit(wxCloseEvent& event)
{
	EndModal(wxID_OK);
	this->Destroy();
}

void CycleTaskDialog::ShowTasks()
{
	this->tasksSizer = new wxBoxSizer(wxVERTICAL);
	for (int i = 0; i < this->user->userCycleTasks.size(); i++)
	{
		auto ctd = new CycleTaskDisp(user->userCycleTasks[i], this, wxDefaultPosition, i);
		this->tasksDisplays.push_back(ctd);
		tasksSizer->Add(ctd);
	}
	this->SetSizer(tasksSizer);
	Layout();
	this->SetSize(wxSize(300, HEIGHT_OFFSET - 70 + TASK_DISP_HEIGHT * this->tasksDisplays.size()));
}

void CycleTaskDialog::HideTasks()
{
	for (auto t : tasksDisplays)
	{
		delete t;
		t = nullptr;
	}
	this->tasksSizer->Clear();
	Layout();
	tasksDisplays.clear();
}

void CycleTaskDialog::UpdateTaskDisp()
{
	this->HideTasks();
	this->ShowTasks();
}


CycleTaskDialog::~CycleTaskDialog()
{
	this->HideTasks();
}

CycleTaskDisp::CycleTaskDisp(CycleTask* _task, CycleTaskDialog* frame, wxPoint placement, int _id) : wxPanel(frame, -1, placement, wxSize(300, TASK_DISP_HEIGHT))
{
	this->task = _task;
	this->id = _id;
	this->frame = frame;
	this->infoSizer = new wxBoxSizer(wxVERTICAL);
	this->allSizer = new wxBoxSizer(wxHORIZONTAL);
	
	this->titleST = new wxStaticText(this, wxID_ANY, _task->GetTitle(), placement, wxSize(200, 20));
	this->descriptionST = new wxStaticText(this, wxID_ANY, _task->GetTitle(), /*wxPoint(placement.x, placement.y + 22)*/ placement, wxSize(200, 20));
	this->infoSizer->Add(titleST, 0, wxALIGN_LEFT | wxLEFT);
	this->infoSizer->Add(descriptionST, 0, wxALIGN_LEFT | wxLEFT);
	
	this->deleteBt = new wxButton(this, wxID_ANY, "Delete", /*wxPoint(placement.x + 205, placement.y + 10)*/ placement, wxSize(50, 30));
	this->deleteBt->Bind(wxEVT_BUTTON, &CycleTaskDisp::OnDeleteClick, this);
	this->allSizer->Add(this->infoSizer, 0);
	this->allSizer->Add(this->deleteBt, 0);
	
	this->SetColor();
	this->titleST->SetFont(wxFont(wxFontInfo(15)));
	this->descriptionST->SetFont(wxFont(wxFontInfo(13)));
	this->SetSizer(allSizer);
	this->SetBackgroundColour(wxColour(200, 200, 200));
	Layout();
}

void CycleTaskDisp::SetColor()
{
	char r = 0;
	char g = 0;
	char b = 0;
	switch (task->GetTaskDifficulty())
	{
	case TaskDifficulty::Easy:
		g = 128;
		break;
	case TaskDifficulty::Medium:
		r = 255;
		g = 250;
		break;
	case TaskDifficulty::Hard:
		r = 255;
		break;
	default:
		break;
	}
	this->descriptionST->SetForegroundColour(wxColour(r, g, b));
	this->titleST->SetForegroundColour(wxColour(r, g, b));
}



void CycleTaskDisp::OnDeleteClick(wxCommandEvent& evt)
{
	this->frame->user->RemoveCycleTask(this->task->GetId());
	this->frame->UpdateTaskDisp();
}

CycleTaskDisp::~CycleTaskDisp()
{
	delete this->titleST;
	delete this->descriptionST;
	delete this->deleteBt;
	this->allSizer->Clear();
	
	this->titleST = nullptr;
	this->descriptionST = nullptr;
	this->deleteBt = nullptr;
}