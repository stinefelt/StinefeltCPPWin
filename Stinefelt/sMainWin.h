#pragma once
#include <wx/wx.h>

class sMainWin : public wxFrame
{
public:
	sMainWin();
	~sMainWin();

	const LPCWSTR PuttyDownloadURL = L"https://the.earth.li/~sgtatham/putty/latest/w64/putty.exe";
	const LPCWSTR PuttyDownloadFileAndPath = L"C:/Stinefelt/Putty.exe";

	wxButton *m_DownloadProgramBtn = nullptr;

	void OnDownloadBtnClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

private:
	void DownloadFile(LPCWSTR URL, LPCWSTR  FileNameAndPath);
};

