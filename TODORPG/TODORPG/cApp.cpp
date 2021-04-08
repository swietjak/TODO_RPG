#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
	m_frame1 = new cMain();
	bool isLogged = false;
	wxString login = "";
	m_frame1->Show();
	/*while (d->ShowModal() == wxID_OK) {
		login = d->usernameInput->GetValue();
		if (login == "chuj")
			m_frame1->titleInput->SetValue("chuuuj");
	}*/
	return true;
}