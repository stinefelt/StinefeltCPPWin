#include <windows.h>
//#include <wx/wx.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")

class DownloadProgress : public IBindStatusCallback {
public:
  int progress = 0;
  int filesize = 0;
  int maxprogress = 0;
  bool AbortDownload = false;
  bool done = false;

  HRESULT __stdcall QueryInterface(const IID&, void**) {
    return E_NOINTERFACE;
  }
  ULONG STDMETHODCALLTYPE AddRef(void) {
    return 1;
  }
  ULONG STDMETHODCALLTYPE Release(void) {
    return 1;
  }
  HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib) {
    return E_NOTIMPL;
  }
  virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority) {
    return E_NOTIMPL;
  }
  virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) {
    return S_OK;
  }
  virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) {
    return E_NOTIMPL;
  }
  virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) {
    return E_NOTIMPL;
  }
  virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) {
    return E_NOTIMPL;
  }
  virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk) {
    return E_NOTIMPL;
  }

  virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
  {
    // TODO: Add a progress bar wxProgressDialog()???
    //wxLogDebug("callback: %ld %ld", ulProgress, ulProgressMax);

    progress = ulProgress;
    maxprogress = ulProgressMax;
    filesize = ulProgressMax;

    if (AbortDownload) {
      done = true;
      return E_ABORT;
    }

    if (ulProgressMax > 0 && ulProgress == ulProgressMax) {
      done = true;
    }

    return S_OK;
  }
};
