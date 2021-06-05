#include "KnownDLL.h"
#include "Util.h"

#include <shared/PeSignatureVerifier/PeSignatureVerifier.h>

using namespace KnownDLL;
using winreg::RegKey;

vector<knowndll_t> KnownDLL::GetDLL() {
  vector<knowndll_t> ret;
  RegKey handle{ HKEY_LOCAL_MACHINE, ENTRY, KEY_READ | KEY_WOW64_64KEY };
  vector<std::pair<wstring, DWORD>> values = handle.EnumValues();
  wstring DLL, DLL32;

  // get base path
  for (const auto& v : values) {
    if (v.second == REG_EXPAND_SZ) {
      if (Util::strcmp_nocase(v.first, wstring(L"dlldirectory"))) DLL = handle.GetExpandStringValue(v.first);
      else if (Util::strcmp_nocase(v.first, wstring(L"dlldirectory32"))) DLL32 = handle.GetExpandStringValue(v.first);
      DLL += L"\\"; DLL32 += L"\\";
    }
  }

  // get full path for each dll
  for (const auto& v : values) {
    if (v.second != REG_SZ) continue;
    // 64 bits
    wstring impa = DLL + handle.GetStringValue(v.first);
    Util::ToFullPath(impa);
    DWORD verify = PeSignatureVerifier::CheckFileSignature(impa);
    ret.push_back(knowndll_t(v.first, verify, impa));

    // 32 bits
    impa = DLL32 + handle.GetStringValue(v.first);
    Util::ToFullPath(impa);
    verify = PeSignatureVerifier::CheckFileSignature(impa);
    ret.push_back(knowndll_t(v.first, verify, impa));
  }

  return ret;
}