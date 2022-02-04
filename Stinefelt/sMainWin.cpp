#include "sMainWin.h"
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include "DownloadProgress.h"
#include <thread>
#include <wx/filefn.h>

wxBEGIN_EVENT_TABLE(sMainWin, wxFrame)
EVT_BUTTON(10001, OnDownloadBtnClicked)
EVT_BUTTON(10002, OnTestBtnClicked)
wxEND_EVENT_TABLE()

sMainWin::sMainWin() : wxFrame(NULL, wxID_ANY, "Stinefelt - Testing Grounds", wxPoint(30, 30), wxSize(800, 420), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	m_DownloadProgramBtn = new wxButton(this, 10001, "Download Test Files", wxPoint(10, 10), wxSize(150, 50));
	m_DownloadTestBtn = new wxButton(this, 10002, "Download Test", wxPoint(170, 10), wxSize(150, 50));
	m_LogListBox = new wxListBox(this, wxID_ANY, wxPoint(10, 70), wxSize(765, 300));
	
	SetBackgroundColour(*wxBLACK);
}

sMainWin::~sMainWin()
{	
	Destroy();
}

void sMainWin::OnDownloadBtnClicked(wxCommandEvent& WXUNUSED(event))
{	
  DoThreadDownloadOperation(TestDownloadURL0, TestDownloadFileAndPath0);
  DoThreadDownloadOperation(TestDownloadURL1, TestDownloadFileAndPath1);
}

void sMainWin::OnTestBtnClicked(wxCommandEvent& evt)
{
  bool bFileExist = wxFileExists(TestDownloadFileAndPath0);
  
  if (bFileExist)
  {
    m_LogListBox->Append("Skipping Download File Exist");
  }
  else
  {
    m_LogListBox->Append("Download Files");
  }
}

static void DownloadFile(const wxString& URL, const wxString& FileNameAndPath, DownloadProgress* progress)
{		
	HRESULT hr = URLDownloadToFile(0, URL, FileNameAndPath, 0, static_cast<IBindStatusCallback*>(progress));
}

void sMainWin::DoThreadDownloadOperation(wxString &TestDownloadUrl, wxString &TestDownloadFileNameAndPath)
{   
  bool abort = false;
  DownloadProgress progressDownload;
  wxProgressDialog progressDialog("Downloading", "Please be patient...", 100, this, wxPD_CAN_ABORT);
  progressDialog.Show();

  std::thread downloadThread(DownloadFile, TestDownloadUrl, TestDownloadFileNameAndPath, &progressDownload);

  while (!progressDownload.done && !abort) {
    if (progressDownload.maxprogress > 0) {
      double progressDouble = (double)progressDownload.progress * 100.0 / progressDownload.maxprogress;
      abort = !progressDialog.Update((int)progressDouble, wxString::Format("Download Progress: %.2f %%", progressDouble));
    }
    else {
      abort = !progressDialog.Pulse("Waiting for download to start...");
      if (abort) {
        progressDownload.AbortDownload = true;
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