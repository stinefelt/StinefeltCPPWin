#pragma once
#include <wx/wx.h>

class sMainWin : public wxFrame
{
public:
	sMainWin();
	~sMainWin();

	wxString TestDownloadURL0 = L"http://ipv4.download.thinkbroadband.com/1GB.zip";
	wxString TestDownloadFileAndPath0 = L"C:/Stinefelt/1GB.zip";
	wxString TestDownloadURL1 = L"http://ipv4.download.thinkbroadband.com/512MB.zip";
	wxString TestDownloadFileAndPath1 = L"C:/Stinefelt/512MB.zip";	

	wxButton *m_DownloadProgramBtn = nullptr;
	wxButton *m_DownloadTestBtn = nullptr;
	wxListBox *m_LogListBox = nullptr;
	wxGauge *m_DownloadGuage = nullptr;

	void OnDownloadBtnClicked(wxCommandEvent& evt);
	void OnTestBtnClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

private:		
	void StartDownloading(wxCommandEvent& WXUNUSED(event));
	void OnQuit(wxCommandEvent& WXUNUSED(event));
	void DoThreadDownloadOperation(wxString& TestDownloadUrl, wxString& TestDownloadFileNameAndPath);	
};

