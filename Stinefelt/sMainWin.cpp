#include "sMainWin.h"
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include "DownloadProgress.h"

wxBEGIN_EVENT_TABLE(sMainWin, wxFrame)
EVT_BUTTON(10001, OnDownloadBtnClicked)
EVT_BUTTON(10002, OnTestBtnClicked)
wxEND_EVENT_TABLE()

sMainWin::sMainWin() : wxFrame(NULL, wxID_ANY, "Stinefelt - Testing Grounds", wxPoint(30, 30), wxSize(800, 420), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	m_DownloadProgramBtn = new wxButton(this, 10001, "Download 100MB", wxPoint(10, 10), wxSize(150, 50));
	m_DownloadTestBtn = new wxButton(this, 10002, "Download Test", wxPoint(170, 10), wxSize(150, 50));
	m_LogListBox = new wxListBox(this, wxID_ANY, wxPoint(10, 70), wxSize(765, 300));

	SetBackgroundColour(*wxBLUE);
}

sMainWin::~sMainWin()
{	
	Destroy();
}

void sMainWin::OnDownloadBtnClicked(wxCommandEvent& evt)
{	
	DownloadFile(TestDownloadURL, TestDownloadFileAndPath);
}

void sMainWin::OnTestBtnClicked(wxCommandEvent& evt)
{
	m_LogListBox->Append("Test Button Clicked.");
}

void sMainWin::DownloadFile(LPCWSTR URL, LPCWSTR FileNameAndPath)
{		
	// Lets get that progress dialog loaded as dialog
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Wait..."), wxT("Keep waiting..."), 100, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);

	// Lets get the download process started
	DownloadProgress progress;
	IBindStatusCallback* callback = (IBindStatusCallback*)&progress;
	HRESULT hr = URLDownloadToFile(0, URL, FileNameAndPath, NULL, static_cast<IBindStatusCallback*>(&progress));
	
	m_LogListBox->Append(std::to_string(progress.GetDownloadProgress()));

	// TODO: Impliment Threadding and Track Download Progress
		
	if (SUCCEEDED(hr))
	{	
		delete dialog;
	}
	else
	{
		delete dialog;
	}
}
