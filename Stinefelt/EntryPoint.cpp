#include "EntryPoint.h"

wxIMPLEMENT_APP(EntryPoint);

EntryPoint::EntryPoint()
{
}

EntryPoint::~EntryPoint()
{
}

bool EntryPoint::OnInit()
{
	sMainWinFrame = new sMainWin();
	sMainWinFrame->Show();

	return true;
}