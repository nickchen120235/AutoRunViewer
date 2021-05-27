#pragma once

#include "shared/WinReg.hpp"
#include <string>
#include <vector>
#include <tuple>

using std::wstring;
using std::vector;
using std::tuple;

namespace Service {
  const wstring ENTRY = L"System\\CurrentControlSet\\Services";
  const DWORD KERNEL = 1;
  const DWORD FS = 2;
  const DWORD ADAP = 4;
  const DWORD RECOG = 8;
  const DWORD SERVICE_OWN = 16;
  const DWORD SERVICE_SHA = 32;
  const DWORD SERVICE_INT = 256;

  // Entry, Description, ImagePath, Verification
  typedef tuple<wstring, wstring, wstring, DWORD> service_t;
  vector<service_t> GetServices();
  vector<service_t> GetDrivers();

  const wstring SYSTEMROOT1 = L"%SystemRoot%";
  const wstring SYSTEMROOT2 = L"\\SystemRoot";
  const wstring SYSTEMROOT3 = L"%systemroot%";
  const wstring WINDIR = L"%windir%";
  void EnvConvert(wstring&);
};