#pragma once
#include <wx/wx.h>
#include "sMainWin.h"

class EntryPoint : public wxApp
{
public:
	EntryPoint();
	~EntryPoint();

	virtual bool OnInit();

private:
	sMainWin* sMainWinFrame = nullptr;
};

