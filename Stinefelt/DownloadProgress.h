#include <windows.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")

class DownloadProgress : public IBindStatusCallback {
public:

  int progress, filesize, maxprogress;
  int AbortDownload;

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
    progress = ulProgress;
    maxprogress = ulProgressMax;
    filesize = ulProgressMax;
    if (AbortDownload) return E_ABORT;
    return S_OK;

    /*std::wcout << ulProgress << L" of " << ulProgressMax;
    if (szStatusText) std::wcout << " " << szStatusText;
    std::wcout << std::endl;*/
    return S_OK;
  }
};