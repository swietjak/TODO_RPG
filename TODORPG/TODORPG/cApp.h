/*@file*/
#pragma once
#include <wx/wx.h>
#include <iostream>
#include "cMain.h"
#include "LoginDialog.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

	virtual bool OnInit();
private:
	cMain* m_frame1 = nullptr;
};

