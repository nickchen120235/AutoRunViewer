#pragma once

#include <shared/WinReg.hpp>
#include <string>
#include <vector>
#include <tuple>

using std::wstring;
using std::vector;
using std::tuple;
using std::pair;

namespace KnownDLL {
  const wstring ENTRY = L"system\\currentcontrolset\\control\\session manager\\knowndlls";

  // entry, verified, imagepath
  typedef tuple<wstring, DWORD, wstring> knowndll_t;
  vector<knowndll_t> GetDLL();
};