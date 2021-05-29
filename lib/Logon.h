#pragma once

#include <shared/WinReg.hpp>
#include <string>
#include <vector>
#include <tuple>

using std::wstring;
using std::vector;
using std::tuple;
using std::pair;

namespace Logon {
  const wstring RUN = L"software\\microsoft\\windows\\currentversion\\run";
  const wstring RUNONCE = L"software\\microsoft\\windows\\currentversion\\runonce";
  const wstring RUNONCEEX = L"software\\microsoft\\windows\\currentversion\\runonceex";

  // entry, verified, imagepath
  typedef tuple<wstring, DWORD, wstring> logon_t;
  // entry, entries
  typedef pair<wstring, vector<logon_t>> roe_t;
  vector<logon_t> GetRun(HKEY);
  vector<logon_t> GetRunOnce(HKEY);
  vector<roe_t> GetRunOnceEx(HKEY);
};