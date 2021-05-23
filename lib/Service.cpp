#include "Service.h"
#include "shared/ServiceLib/ServiceController.h" // from https://www.codeproject.com/Articles/1098263/Interact-with-Windows-Services-in-Cplusplus

#include <iostream>
#include <optional>

using std::wcout;
using std::endl;
using std::optional;
using winreg::RegKey;
using winreg::RegException;

vector<Service::service_t> Service::GetServices() {
  vector<Service::service_t> ser; // returned vector

  RegKey handler{ HKEY_LOCAL_MACHINE, Service::ENTRY }; // main key
  vector<wstring> sub = handler.EnumSubKeys(); // all services and drivers
  handler.Close();

  for (const auto& s : sub) { // go through each subkey
    try {
      handler.Open(HKEY_LOCAL_MACHINE, Service::ENTRY + L"\\" + s);
      DWORD type = handler.GetDwordValue(L"Type");

      if ((type & Service::SERVICE_OWN) || (type & Service::SERVICE_SHA) || (type & Service::SERVICE_INT)) {
        auto service = ServiceController{ s };
        wstring desc = service.GetServiceConfig().GetDescription();
        wstring impa = service.GetServiceConfig().GetBinaryPathName();

        if (impa.find(L"svchost") != wstring::npos) { // get dll from /parameters/servicedll if executed by svchost
          RegKey parameter{ HKEY_LOCAL_MACHINE, Service::ENTRY + L"\\" + s + L"\\parameters" };
          impa = parameter.GetExpandStringValue(L"ServiceDll");
          Service::EnvConvert(impa);
        }

        ser.push_back(service_t(s, desc, impa, type));
      }

      handler.Close();
    }
    catch (const RegException& e) { // "Type" may be missing, just ignore it
      (void)e;
      continue;
    }
  }

  return ser;
}

vector<Service::service_t> Service::GetDrivers() {
  vector<service_t> drv;

  RegKey handler{ HKEY_LOCAL_MACHINE, Service::ENTRY }; // main key
  vector<wstring> sub = handler.EnumSubKeys(); // all services and drivers
  handler.Close();

  for (const auto& s : sub) {
    try {
      handler.Open(HKEY_LOCAL_MACHINE, Service::ENTRY + L"\\" + s);
      DWORD type = handler.GetDwordValue(L"Type");

      if ((type & Service::KERNEL) || (type & Service::FS) || (type & Service::ADAP) || (type & Service::RECOG)) {
        auto service = ServiceController{ s };
        wstring desc = service.GetServiceName();
        wstring impa = handler.GetExpandStringValue(L"ImagePath");
        Service::EnvConvert(impa);
        drv.push_back(service_t(s, desc, impa, type));
      }

      handler.Close();
    }
    catch (const RegException& e) {
      (void)e;
      continue;
    }
  }

  return drv;
}

void Service::EnvConvert(wstring& impa) {
  std::size_t env = impa.find(Service::SYSTEMROOT1);
  if (env != wstring::npos) impa.replace(env, Service::SYSTEMROOT1.length(), L"C:\\Windows");
  env = impa.find(Service::WINDIR);
  if (env != wstring::npos) impa.replace(env, Service::WINDIR.length(), L"C:\\Windows");
  env = impa.find(Service::SYSTEMROOT2);
  if (env != wstring::npos) impa.replace(env, Service::SYSTEMROOT2.length(), L"C:\\Windows");
  env = impa.find(Service::SYSTEMROOT3);
  if (env != wstring::npos) impa.replace(env, Service::SYSTEMROOT3.length(), L"C:\\Windows");
  if (impa.find(L"system32") == 0 || impa.find(L"System32") == 0) impa.insert(0, L"C:\\Windows\\");
}