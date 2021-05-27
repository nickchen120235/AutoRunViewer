#include "Util.h"

void Util::ToFullPath(std::wstring& path) {
  DWORD apiret = 0;
  TCHAR buf[4096] = L"\0";
  apiret = ExpandEnvironmentStrings(path.c_str(), buf, 4096);
  if (apiret == 0) return;
  else path = std::wstring(buf);
}