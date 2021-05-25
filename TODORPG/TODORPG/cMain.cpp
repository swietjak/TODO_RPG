#include "cMain.h" 
#define SUBMIT_BTN_ID 10001

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "main") {
	this->SetSize(wxSize(WINDOW_WIDTH, WINDOW_HEIGHT_USERLES));
	this->loginButton = new wxButton(this, SUBMIT_BTN_ID, "Login", wxPoint(10, 10), wxSize(150, 50));
	this->registerButton = new wxButton(this, SUBMIT_BTN_ID, "Register", wxPoint(170, 10), wxSize(150, 50));
	loginButton->Bind(wxEVT_BUTTON, &cMain::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &cMain::OnRegisterButtonClicked, this);
	this->ul = new UsersList("data.json");
	DisplayRanking();
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
		return;
	}
	while (d->ShowModal() == wxID_CANCEL)
	{
		d->Destroy();
	}
}

void cMain::ChangeDisplayAfterLogin()
{
	this->InitSizer();
	delete this->loginButton;
	delete this->registerButton;
	delete this->listView;
	this->listView = nullptr;
	this->loginButton = nullptr;
	this->registerButton = nullptr;
	this->addTaskButton = new wxButton(this, wxID_ANY, "Add task", wxPoint(280, 17), wxSize(60, 26));
	this->logoutButton = new wxButton(this, wxID_ANY, "Log out", wxPoint(350, 17), wxSize(60, 26));
	this->btnsSizer->Add(this->addTaskButton, 0); 
	this->btnsSizer->Add(20, -1);
	this->btnsSizer->Add(this->logoutButton, 0);

	this->usernameST = new wxStaticText(this, wxID_ANY, ReturnUsernameMsg(), wxPoint(10, 10), wxSize(200, 20));
	this->levelST = new wxStaticText(this, wxID_ANY, ReturnLevelMsg(), wxPoint(10, 30), wxSize(150, 20));
	this->usrSizer->Add(this->usernameST, 0, wxALIGN_LEFT | wxLEFT);
	this->usrSizer->Add(this->levelST, 0, wxALIGN_LEFT | wxLEFT);
	this->addTaskButton->Bind(wxEVT_BUTTON, &cMain::onClickAddTaskFunction, this);
	this->logoutButton->Bind(wxEVT_BUTTON, &cMain::onClickLogoutFunction, this);

	this->navSizer->Add(this->usrSizer, 0);
	this->navSizer->AddSpacer(50);
	
	this->allSizer->Add(-1, 5);
	this->navSizer->Add(this->btnsSizer, 0);
	this->allSizer->Add(this->navSizer, 0, wxALIGN_LEFT | wxLEFT, 20);
	this->allSizer->Add(-1, 10);

	this->DisplayTasks();
	this->allSizer->Add(this->tasksSizer, 0, wxALIGN_LEFT | wxLEFT);

	if (this->currentUser->GetLevel() > 1 && this->currentUser->userCycleTasks.size() > 0)
	{
		this->cycleTasksButton = new wxButton(this, wxID_ANY, "Cycle tasks", wxPoint(10, 60 + TASK_DISP_HEIGHT * tasksDisplays.size()), wxSize(65, 25));
		this->cycleTasksButton->Bind(wxEVT_BUTTON, &cMain::OnCyckleTaskClicked, this);
		this->allSizer->Add(this->cycleTasksButton, 0, wxALIGN_LEFT | wxLEFT);
	}

	this->usernameST->SetFont(wxFont(wxFontInfo(15)));
	this->levelST->SetFont(wxFont(wxFontInfo(15)));
	this->SetSize(wxSize(WINDOW_WIDTH, HEIGHT_OFFSET + TASK_DISP_HEIGHT * tasksDisplays.size()));
	this->SetSizer(this->allSizer);
	Layout();
}

void cMain::DisplayTasks()
{
	int i = 0;
	for (auto task : currentUser->userTasks)
	{
		auto point = wxPoint(taskStart.x, taskStart.y + i++ * TASK_DISP_HEIGHT);
		auto td = new TaskDisplay(task, wxDefaultPosition, this);
		this->tasksSizer->Add(td, 1, wxALIGN_LEFT | wxLEFT, 20);
		this->tasksDisplays.push_back(td);
	}
	this->SetSize(wxSize(WINDOW_WIDTH, HEIGHT_OFFSET + TASK_DISP_HEIGHT * tasksDisplays.size()));
	this->Layout();
}

void cMain::InitSizer()
{
	allSizer = new wxBoxSizer(wxVERTICAL);
	navSizer = new wxBoxSizer(wxHORIZONTAL);
	tasksSizer = new wxBoxSizer(wxVERTICAL);
	usrSizer = new wxBoxSizer(wxVERTICAL);
	btnsSizer = new wxBoxSizer(wxHORIZONTAL);
}

void cMain::ClearSizers()
{

}

void cMain::HideTasks()
{
	for (auto tdisp : this->tasksDisplays)
	{
		delete tdisp;
		tdisp = nullptr;
	}
	this->tasksDisplays.clear();
	/*delete this->cycleTasksButton;
	this->cycleTasksButton = nullptr;*/
	this->tasksSizer->Clear();
}

void cMain::UpdateTaskDisp()
{
	this->HideTasks();
	this->DisplayTasks();
	this->Layout();
}

void cMain::DisplayRanking()
{
	this->listView = new wxListView(this, wxID_ANY, wxPoint(10, 70), wxSize(250, 200));
	this->listView->AppendColumn("name");
	this->listView->AppendColumn("level");
	this->listView->AppendColumn("experience");
	this->listView->DeleteAllItems();
	int i = 0;
	for (auto usr : ul->GetUsersStats())
	{
		auto stats = usr.second;
		this->listView->InsertItem(i, usr.first);
		this->listView->SetItem(i, 1, std::to_string(stats.first));
		this->listView->SetItem(i, 2, std::to_string(stats.second));
	}
}

void cMain::ChangeDisplayAfterLogout()
{
	delete this->addTaskButton;
	delete this->logoutButton;
	delete this->usernameST;
	delete this->levelST;
	delete this->cycleTasksButton;

	this->addTaskButton = nullptr;
	this->logoutButton = nullptr;
	this->usernameST = nullptr;
	this->levelST = nullptr;
	this->cycleTasksButton = nullptr;
	this->currentUser = nullptr;

	this->HideTasks();

	this->loginButton = new wxButton(this, SUBMIT_BTN_ID, "Login", wxPoint(10, 10), wxSize(150, 50));
	this->registerButton = new wxButton(this, SUBMIT_BTN_ID, "Register", wxPoint(170, 10), wxSize(150, 50));
	loginButton->Bind(wxEVT_BUTTON, &cMain::OnLoginButtonClicked, this);
	registerButton->Bind(wxEVT_BUTTON, &cMain::OnRegisterButtonClicked, this);
	DisplayRanking();
	this->SetSize(wxSize(WINDOW_WIDTH, WINDOW_HEIGHT_USERLES));
}

void cMain::OnRegisterButtonClicked(wxCommandEvent& evt)
{
	auto d = new RegisterDialog("register", this->ul);
	while (d->ShowModal() == wxID_OK)
	{
		d->Destroy();
	}
	DisplayRanking();
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
		return;
	}
	while (d->ShowModal() == wxID_CANCEL)
	{
		return;
	}
}

void cMain::AppendLastTaskDisp()
{
	auto point = wxPoint(taskStart.x, taskStart.y + (currentUser->userTasks.size() - 1) * TASK_DISP_HEIGHT);
	auto td = new TaskDisplay(currentUser->userTasks.back(), point, this);
	this->tasksDisplays.push_back(td);
	this->tasksSizer->Add(td);
	//this->cycleTasksButton->SetPosition(wxPoint(10, 60 + TASK_DISP_HEIGHT * tasksDisplays.size()));
	this->SetSize(wxSize(WINDOW_WIDTH, HEIGHT_OFFSET + TASK_DISP_HEIGHT * tasksDisplays.size()));
	this->Layout();
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
		if ((diff > t->GetTimesUsed()) && (!currentUser->FindTask(t->GetId())))
		{
			currentUser->AddTask(new Task(*static_cast<Task*>(t)), time(0));
			this->AppendLastTaskDisp();
			t->IncrementTimesUsed();
		}
	}
	this->ul->UpdateJson();
}

void cMain::OnCyckleTaskClicked(wxCommandEvent& evt)
{
	auto d = new CycleTaskDialog(this->currentUser);
	while (d->ShowModal() == wxID_OK)
	{
		this->ul->UpdateJson();
		d->Destroy();
	}
}


TaskDisplay::TaskDisplay(Task* _task, wxPoint _placement, cMain* _frame) : wxPanel(_frame, -1, _placement, wxSize(400, TASK_DISP_HEIGHT))
{
	this->InitSizers();
	this->frame = _frame;
	this->id = _task->GetId();
	auto time = _task->GetExpirationDate();
	this->titleST = new wxStaticText(this, wxID_ANY, _task->GetTitle(), _placement, wxSize(200, 20));
	this->dateST = new wxStaticText(this, wxID_ANY, ctime(&time), _placement /*wxPoint(_placement.x + 200, _placement.y)*/, wxSize(140, 18));
	this->upperInfoSizer->Add(this->titleST, 0);
	this->upperInfoSizer->Add(this->dateST, 0);
	this->infoSizer->Add(this->upperInfoSizer, 0, wxALIGN_LEFT | wxLEFT);
	
	this->descriptionST = new wxStaticText(this, wxID_ANY, _task->GetDescription(), _placement /*wxPoint(_placement.x, _placement.y + 22)*/, wxSize(200, 18));
	this->infoSizer->Add(this->descriptionST, 0, wxALIGN_LEFT | wxLEFT);
	this->taskSizer->Add(this->infoSizer, 0);

	this->doneBT = new wxButton(this, wxID_ANY, "Done", _placement /*wxPoint(_placement.x + 350, _placement.y + 5)*/, wxSize(50, 30));
	this->taskSizer->Add(this->doneBT, 0);

	this->doneBT->Bind(wxEVT_BUTTON, &TaskDisplay::onClickDelete, this);
	this->titleST->SetFont(wxFont(wxFontInfo(13)));
	this->SetColor(_task->GetTaskDifficulty());
	this->SetSizer(this->taskSizer);
	this->SetBackgroundColour(wxColour(170, 170, 170));
	Layout();
}

void TaskDisplay::InitSizers()
{
	upperInfoSizer = new wxBoxSizer(wxHORIZONTAL);
	infoSizer = new wxBoxSizer(wxVERTICAL);
	taskSizer = new wxBoxSizer(wxHORIZONTAL);
}

void TaskDisplay::onClickDelete(wxCommandEvent& event)
{
	frame->ul->RemoveTask(frame->currentUser->username.c_str(), this->id);
	frame->UpdateLevel();
	OutputDebugStringA(std::to_string(frame->currentUser->GetExperience()).c_str());
	frame->UpdateTaskDisp();
}

void TaskDisplay::SetColor(TaskDifficulty td)
{
	char r = 0;
	char g = 0;
	char b = 0;
	switch (td)
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
	this->dateST->SetForegroundColour(wxColour(r, g, b));
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