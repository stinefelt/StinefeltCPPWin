#include <windows.h>
#include <urlmon.h>
#include <iostream>

#pragma comment(lib, "urlmon.lib")

class DownloadProgress : public IBindStatusCallback {
public:
  ULONG DProgress;
  ULONG DProgressStart;
  ULONG GetDownloadProgress() { return DProgress; }
  ULONG GetDownloadStartProgress() { return DProgressStart; }
private:
  void SetDownloadProgress(ULONG DProgress) { DProgress = this->DProgress; }
  void SetDownloadStartProgress(ULONG DProgressStart) { DProgressStart = this->DProgressStart; }
public:
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
    if (ulProgress != 0)
    {
      double* percentage = new double(ulProgress * 1.0 / ulProgressMax * 100); 
      SetDownloadProgress((ULONG)*percentage);
      delete percentage;
      return S_OK;
    }
  }
};