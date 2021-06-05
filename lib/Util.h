#pragma once

#include <Windows.h>
#include <string>

namespace Util {
  void ToFullPath(std::wstring&);
  inline bool strcmp_nocase(const std::wstring& str1, const std::wstring& str2) {
    if (str1.length() != str2.length()) return false;
    else return equal(str1.begin(), str1.end(), str2.begin(), str2.end(), [](const wchar_t& c1, const wchar_t& c2) {return (c1 == c2 || towupper(c1) == towupper(c2)); });
  }
};