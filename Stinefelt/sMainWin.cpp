#include "sMainWin.h"
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include "DownloadProgress.h"

wxBEGIN_EVENT_TABLE(sMainWin, wxFrame)
EVT_BUTTON(10001, OnDownloadBtnClicked)
wxEND_EVENT_TABLE()

sMainWin::sMainWin() : wxFrame(NULL, wxID_ANY, "Stinefelt - Testing Grounds", wxPoint(30, 30), wxSize(800, 420), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	m_DownloadProgramBtn = new wxButton(this, 10001, "Download Putty", wxPoint(10, 10), wxSize(150, 50));
	m_DownloadProgramBtn = new wxButton(this, 10001, "Dummy Button", wxPoint(170, 10), wxSize(150, 50));

	SetBackgroundColour(*wxBLUE);
}

sMainWin::~sMainWin()
{
	Destroy();
}

void sMainWin::OnDownloadBtnClicked(wxCommandEvent& evt)
{
	DownloadFile(PuttyDownloadURL, PuttyDownloadFileAndPath);
}

void sMainWin::DownloadFile(LPCWSTR URL, LPCWSTR FileNameAndPath)
{
	// Lets get that progress dialog loaded as dialog
	wxProgressDialog* dialog = new wxProgressDialog(wxT("Wait..."), wxT("Keep waiting..."), 100, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);

	// Lets get the download process started
	DownloadProgress progress;
	HRESULT hr = URLDownloadToFile(0, URL, FileNameAndPath, 0, static_cast<IBindStatusCallback*>(&progress));

	// I don't know how to referece to &progress, but here goes an attempt.
	for (int i = 0; i < progress.maxprogress; i++) {
		wxMilliSleep(15);
		if (i % 23) dialog->Update(i);
	}
	// Update the Progress Bar with the progress of the download?
	dialog->Update(progress.progress);
	// Let's clear this to keep mem happy
	delete dialog;
}
