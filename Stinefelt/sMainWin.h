#pragma once
#include <wx/wx.h>

class sMainWin : public wxFrame
{
public:
	sMainWin();
	~sMainWin();

	const LPCWSTR PuttyDownloadURL = L"http://ipv4.download.thinkbroadband.com/5MB.zip";
	const LPCWSTR PuttyDownloadFileAndPath = L"C:/Stinefelt/1GB.zip";

	wxButton *m_DownloadProgramBtn = nullptr;
	wxListBox* m_LogListBox = nullptr;

	void OnDownloadBtnClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

private:
	void DownloadFile(LPCWSTR URL, LPCWSTR  FileNameAndPath);	
};

