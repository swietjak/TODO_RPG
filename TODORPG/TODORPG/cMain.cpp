#include "cMain.h" 
#define SUBMIT_BTN_ID 10001

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "main") {
	this->loginButton = new wxButton(this, SUBMIT_BTN_ID, "Login", wxPoint(10, 10), wxSize(150, 50));
	this->registerButton = new wxButton(this, SUBMIT_BTN_ID, "Register", wxPoint(170, 10), wxSize(150, 50));
	loginButton->Bind(wxEVT_BUTTON, &cMain::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &cMain::OnRegisterButtonClicked, this);
	this->ul = new UsersList("data.json");
}

cMain::~cMain()
{
	delete this->ul;
	this->ul = nullptr;
	HideTasks();
	Destroy();
}

void cMain::OnLoginButtonClicked(wxCommandEvent& evt) {
	auto d = new LoginDialog("zaloguj sie", this->ul);
	while (d->ShowModal() == wxID_OK)
	{
		this->currentUser = d->GetResult();
		this->ChangeDisplayAfterLogin();
		this->AppendCycleTasks();
	}
}

void cMain::ChangeDisplayAfterLogin()
{
	delete this->loginButton;
	delete this->registerButton;
	this->loginButton = nullptr;
	this->registerButton = nullptr;
	this->addTaskButton = new wxButton(this, wxID_ANY, "Add task", wxPoint(180, 17), wxSize(60, 26));
	this->logoutButton = new wxButton(this, wxID_ANY, "Log out", wxPoint(250, 17), wxSize(60, 26));
	this->usernameST = new wxStaticText(this, wxID_ANY, ReturnUsernameMsg(), wxPoint(10, 10), wxSize(150, 20));
	this->levelST = new wxStaticText(this, wxID_ANY, ReturnLevelMsg(), wxPoint(10, 30), wxSize(150, 20));
	this->addTaskButton->Bind(wxEVT_BUTTON, &cMain::onClickAddTaskFunction, this);
	this->logoutButton->Bind(wxEVT_BUTTON, &cMain::onClickLogoutFunction, this);
	
	this->DisplayTasks();
	
	this->usernameST->SetFont(wxFont(wxFontInfo(15)));
	this->levelST->SetFont(wxFont(wxFontInfo(15)));
}

void cMain::DisplayTasks()
{
	int i = 0;
	for (auto task: currentUser->userTasks)
	{
		auto point = wxPoint(taskStart.x, taskStart.y + i++*TASK_DISP_HEIGHT);
		this->tasksDisplays.push_back(new TaskDisplay(task, point, this));
	}
}

void cMain::HideTasks()
{
	for (auto tdisp : this->tasksDisplays)
	{
		delete tdisp;
		tdisp = nullptr;
	}
	this->tasksDisplays.clear();
}

void cMain::UpdateTaskDisp()
{
	this->HideTasks();
	this->DisplayTasks();
}

void cMain::ChangeDisplayAfterLogout()
{
	delete this->addTaskButton;
	delete this->logoutButton;
	delete this->usernameST;
	delete this->levelST;

	this->addTaskButton = nullptr;
	this->logoutButton = nullptr;
	this->usernameST = nullptr;
	this->levelST = nullptr;
	
	this->currentUser = nullptr;

	this->HideTasks();
	
	this->loginButton = new wxButton(this, SUBMIT_BTN_ID, "Login", wxPoint(10, 10), wxSize(150, 50));
	this->registerButton = new wxButton(this, SUBMIT_BTN_ID, "Register", wxPoint(170, 10), wxSize(150, 50));
	loginButton->Bind(wxEVT_BUTTON, &cMain::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &cMain::OnRegisterButtonClicked, this);
}

void cMain::OnRegisterButtonClicked(wxCommandEvent& evt)
{
	auto d = new RegisterDialog("register", this->ul);
	while (d->ShowModal() == wxID_OK)
	{
		d->Destroy();
	}
}

void cMain::onClickAddTaskFunction(wxCommandEvent& event) 
{
	if (currentUser->GetLevel() == 1 and currentUser->GetTasksNumber() > 2)
	{
		auto d = new MessageDialog("Warning", "You need to be on level 2 to add more tasks");
		while (d->ShowModal() == wxID_OK)
		{
			d->Destroy();
		}
		return;
	}

	auto d = new TaskInputDialog("zaloguj sie", this->currentUser);
	while (d->ShowModal() == wxID_OK)
	{
		this->ul->UpdateJson();
		this->AppendLastTaskDisp();
		d->Destroy();
	}
}

void cMain::AppendLastTaskDisp()
{
	auto point = wxPoint(taskStart.x, taskStart.y + (currentUser->userTasks.size() - 1) * TASK_DISP_HEIGHT);
	this->tasksDisplays.push_back(new TaskDisplay(currentUser->userTasks.back(), point, this));
}

void cMain::onClickLogoutFunction(wxCommandEvent& event)
{
	this->ChangeDisplayAfterLogout();
}

void cMain::UpdateLevel()
{
	this->levelST->SetLabelText(ReturnLevelMsg());
}

std::string cMain::ReturnUsernameMsg()
{
	return "USERNAME: " + this->currentUser->username;
}

std::string cMain::ReturnLevelMsg()
{
	return "LEVEL: " + std::to_string(this->currentUser->GetLevel());
}

void cMain::AppendCycleTasks()
{
	for (auto t : currentUser->userCycleTasks)
	{
		auto diff = ((time(0) - t->GetCreatedAt()) / DAY);
		if ( (diff > t->GetTimesUsed()) && (!currentUser->FindTask(t->GetId())))
		{
			currentUser->AddTask(static_cast<Task*>(t), time(0));
			this->AppendLastTaskDisp();
			t->IncrementTimesUsed();
		}
	}
	this->ul->UpdateJson();
}

TaskDisplay::TaskDisplay(Task* _task, wxPoint _placement, cMain* _frame)
{
	auto time = _task->GetExpirationDate();
	this->titleST = new wxStaticText(_frame, wxID_ANY, _task->GetTitle(), _placement, wxSize(200, 20));
	this->dateST = new wxStaticText(_frame, wxID_ANY, ctime(&time), wxPoint(_placement.x + 200, _placement.y), wxSize(140, 18));
	this->descriptionST = new wxStaticText(_frame, wxID_ANY, _task->GetDescription(), wxPoint(_placement.x, _placement.y + 22), wxSize(200, 18));
	
	this->doneBT = new wxButton(_frame, wxID_ANY, "Done", wxPoint(_placement.x + 350, _placement.y + 5), wxSize(50, 30));
	this->frame = _frame;
	this->id = _task->GetId();
	this->doneBT->Bind(wxEVT_BUTTON, &TaskDisplay::onClickDelete, this);
	this->titleST->SetFont(wxFont(wxFontInfo(13)));
}

void TaskDisplay::onClickDelete(wxCommandEvent& event)
{
	frame->ul->RemoveTask(frame->currentUser->username.c_str(), this->id);
	frame->UpdateLevel();
	OutputDebugStringA(std::to_string(frame->currentUser->GetExperience()).c_str());
	frame->UpdateTaskDisp();
}

TaskDisplay::~TaskDisplay()
{
	delete this->titleST;
	delete this->dateST;
	delete this->descriptionST;
	delete this->doneBT;

	this->titleST = nullptr;
	this->dateST = nullptr;
	this->descriptionST = nullptr;
	this->doneBT = nullptr;
}
