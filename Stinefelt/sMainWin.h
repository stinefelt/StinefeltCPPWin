#pragma once
#include <wx/wx.h>

class sMainWin : public wxFrame
{
public:
	sMainWin();
	~sMainWin();

	const LPCWSTR TestDownloadURL = L"http://ipv4.download.thinkbroadband.com/512MB.zip";
	const LPCWSTR TestDownloadFileAndPath = L"C:/Stinefelt/512MB.zip";

	wxButton *m_DownloadProgramBtn = nullptr;
	wxButton *m_DownloadTestBtn = nullptr;
	wxListBox* m_LogListBox = nullptr;

	void OnDownloadBtnClicked(wxCommandEvent& evt);
	void OnTestBtnClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

private:
	void DownloadFile(LPCWSTR URL, LPCWSTR  FileNameAndPath);	
};

