#include "sMainWin.h"
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include "DownloadProgress.h"
#include <thread>

wxBEGIN_EVENT_TABLE(sMainWin, wxFrame)
EVT_BUTTON(10001, StartDownloading)
EVT_BUTTON(10002, OnTestBtnClicked)
wxEND_EVENT_TABLE()

sMainWin::sMainWin() : wxFrame(NULL, wxID_ANY, "Stinefelt - Testing Grounds", wxPoint(30, 30), wxSize(800, 420), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	m_DownloadProgramBtn = new wxButton(this, 10001, "Download 100MB", wxPoint(10, 10), wxSize(150, 50));
	m_DownloadTestBtn = new wxButton(this, 10002, "Download Test", wxPoint(170, 10), wxSize(150, 50));
	m_LogListBox = new wxListBox(this, wxID_ANY, wxPoint(10, 70), wxSize(765, 300));
	
	SetBackgroundColour(*wxBLACK);
}

sMainWin::~sMainWin()
{	
	Destroy();
}

void sMainWin::OnDownloadBtnClicked(wxCommandEvent& evt)
{	
  
}

void sMainWin::OnTestBtnClicked(wxCommandEvent& evt)
{
	m_LogListBox->Append("Test Button Clicked.");	
}

static void DownloadFile(const wxString& URL, const wxString& FileNameAndPath, DownloadProgress* progress)
{		
	HRESULT hr = URLDownloadToFile(0, URL, FileNameAndPath, 0, static_cast<IBindStatusCallback*>(progress));
}

void sMainWin::StartDownloading(wxCommandEvent& WXUNUSED(event))
{
  wxProgressDialog progressDialog("Download", "Waiting for download to start...", 100, this, wxPD_CAN_ABORT);
  progressDialog.Show();

  //wxString URL = "http://ipv4.download.thinkbroadband.com/50MB.zip";
  // wxString URL = "http://ipv4.download.thinkbroadband.com/200MB.zip";
  wxString URL = "http://ipv4.download.thinkbroadband.com/1GB.zip";
  const wxString FileNameAndPath = "C:\\Stinefelt\\1GB.zip";
  wxRemove(FileNameAndPath);

  DownloadProgress progress;
  std::thread downloadThread(DownloadFile, URL, FileNameAndPath, &progress);

  bool abort = false;
  while (!progress.done && !abort) {
    if (progress.maxprogress > 0) {
      double progressDouble = (double)progress.progress * 100.0 / progress.maxprogress;
      abort = !progressDialog.Update((int)progressDouble, wxString::Format("Download Progress: %.2f %%", progressDouble));
    }
    else {
      abort = !progressDialog.Pulse("Waiting for download to start...");
      if (abort) {
        progress.AbortDownload = true;
      }
    }
    ::wxMilliSleep(200);
  }
  downloadThread.join();
}

void sMainWin::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  // true is to force the frame to close
  Close(true);
}