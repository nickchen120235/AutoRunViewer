#include "Logon.h"
#include "Util.h"

#include <shared/PeSignatureVerifier/PeSignatureVerifier.h>
#include <qdebug.h>

using namespace Logon;
using winreg::RegKey;
using winreg::RegException;

vector<logon_t> Logon::GetRun(HKEY h) {
  vector<logon_t> run;
  RegKey handle{ h, RUN };
  vector<std::pair<wstring, DWORD>> val = handle.EnumValues();
  qDebug() << "val.size() = " << val.size() << "\n";
  for (const auto& v : val) {
    try {
      qDebug() << "v.first = " << v.first << "\n";
      wstring impa = handle.GetStringValue(v.first);

      size_t clean;
      if ((clean = impa.rfind(L"exe")) != wstring::npos) impa.erase(clean + 3);
      while ((clean = impa.find(L"\"")) != wstring::npos) impa.replace(clean, 1, L"");

      DWORD verify = PeSignatureVerifier::CheckFileSignature(impa);

      run.push_back(logon_t(v.first, verify, impa));
    }
    catch (const RegException& e) {
      (void)e;
      continue;
    }
  }
  qDebug() << "run.size() = " << run.size() << "\n";
  return run;
}

vector<logon_t> Logon::GetRunOnce(HKEY h) {
  vector<logon_t> run;
  RegKey handle{ h, RUNONCE };
  vector<std::pair<wstring, DWORD>> val = handle.EnumValues();
  for (const auto& v : val) {
    try {
      wstring impa = handle.GetStringValue(v.first);

      size_t clean;
      if ((clean = impa.rfind(L"exe")) != wstring::npos) impa.erase(clean + 3);
      while ((clean = impa.find(L"\"")) != wstring::npos) impa.replace(clean, 1, L"");

      DWORD verify = PeSignatureVerifier::CheckFileSignature(impa);

      run.push_back(logon_t(v.first, verify, impa));
    }
    catch (const RegException& e) {
      (void)e;
      continue;
    }
  }
  return run;
}

vector<roe_t> Logon::GetRunOnceEx(HKEY h) {
  vector<roe_t> run;
  RegKey handle{ h, RUNONCEEX };
  vector<wstring> sub = handle.EnumSubKeys();
  for (const auto& s : sub) {
    try {
      handle.Open(h, RUNONCEEX + L"\\" + s);
      vector<pair<wstring, DWORD>> val = handle.EnumValues();
      vector<logon_t> cmd;
      for (int i = 1; i < val.size(); ++i) {
        wstring impa = handle.GetStringValue(val[i].first);
        DWORD verify = PeSignatureVerifier::CheckFileSignature(impa);
        cmd.push_back(logon_t(val[i].first, verify, impa));
      }
      run.push_back(roe_t(s, cmd));
    }
    catch (const RegException& e) {
      (void)e;
      continue;
    }
  }
  return run;
}