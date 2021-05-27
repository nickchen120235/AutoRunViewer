#include "Task.h"
#include "Util.h"

#include <shared/PeSignatureVerifier/PeSignatureVerifier.h>

vector<Task::task_t> Task::GetTasks() {
  vector<task_t> tasks;

  /* Let Qt handle COM */
  // COM initialization
  /*
  HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    exit(EXIT_FAILURE);
  }
  */

  // COM security initialization
  HRESULT hr = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, 0, nullptr);
  if (FAILED(hr)) {
    CoUninitialize();
    exit(EXIT_FAILURE);
  }

  // ITaskService
  ITaskService* service = nullptr;
  hr = CoCreateInstance(CLSID_TaskScheduler, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskService, (LPVOID*)&service);
  if (FAILED(hr)) {
    CoUninitialize();
    exit(EXIT_FAILURE);
  }

  // connect to local task service
  hr = service->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t());
  if (FAILED(hr)) {
    service->Release();
    CoUninitialize();
    exit(EXIT_FAILURE);
  }

  ITaskFolder* root = nullptr;
  hr = service->GetFolder(_bstr_t(L"\\"), &root);
  if (FAILED(hr)) exit(EXIT_FAILURE);

  deque<wstring> path_dq;

  Task::_walk_folders(tasks, root, path_dq);

  root->Release();
  service->Release();
  // CoUninitialize(); // Qt will handle COM

  return tasks;
}

void Task::_walk_folders(vector<Task::task_t>& tasks, ITaskFolder* root, deque<wstring>& path_dq) {
  ITaskFolderCollection* folders = nullptr;
  HRESULT hr = root->GetFolders(0, &folders);

  BSTR curr_name = nullptr;
  hr = root->get_Name(&curr_name);
  if (SUCCEEDED(hr)) {
    path_dq.push_back(wstring(curr_name, SysStringLen(curr_name)));
    //wcout << path_dq.back() << L"\t" << path_dq.size() << endl;
  }

  Task::_walk_tasks(tasks, root, path_dq);
  if (SUCCEEDED(hr)) {
    LONG folders_count = 0;
    hr = folders->get_Count(&folders_count);
    if (folders_count != 0) {
      for (LONG i = 0; i < folders_count; ++i) {
        ITaskFolder* f = nullptr;
        hr = folders->get_Item(_variant_t(i + 1), &f);
        if (FAILED(hr)) return;
        Task::_walk_folders(tasks, f, path_dq);
        path_dq.pop_back();
      }
    }
  }
}

void Task::_walk_tasks(vector<Task::task_t>& tasks, ITaskFolder* folder, deque<wstring>& path_dq) {
  IRegisteredTaskCollection* task_collection = nullptr;
  HRESULT hr = folder->GetTasks(TASK_ENUM_HIDDEN, &task_collection);
  if (FAILED(hr)) return;
  LONG tasks_count = 0;
  hr = task_collection->get_Count(&tasks_count);
  if (tasks_count == 0) return;

  for (LONG i = 0; i < tasks_count; ++i) {
    wstring task_name, task_desc, task_path; // to be inserted
    IRegisteredTask* task = nullptr;
    hr = task_collection->get_Item(_variant_t(i + 1), &task);
    if (SUCCEEDED(hr)) {

      BSTR task_name_bstr = nullptr;
      hr = task->get_Name(&task_name_bstr);
      if (SUCCEEDED(hr)) {
        for (unsigned i = 1; i < path_dq.size(); ++i) {
          task_name += L"\\";
          task_name += path_dq[i];
        }
        task_name += L"\\";
        task_name += wstring(task_name_bstr, SysStringLen(task_name_bstr)); // task_name complete

        ITaskDefinition* def = nullptr;
        hr = task->get_Definition(&def);
        if (SUCCEEDED(hr)) { // get description
          IRegistrationInfo* info = nullptr;
          hr = def->get_RegistrationInfo(&info);
          if (SUCCEEDED(hr)) {
            BSTR task_desc_bstr = nullptr;
            hr = info->get_Description(&task_desc_bstr);
            if (SUCCEEDED(hr)) {
              task_desc = wstring(task_desc_bstr, SysStringLen(task_desc_bstr)); // task_desc complete
            } // info->get_Description(&task_desc_bstr)
          } // def->get_RegistrationInfo(&info)

          IActionCollection* actions = nullptr;
          hr = def->get_Actions(&actions);
          if (SUCCEEDED(hr)) { // get image path
            IAction* action = nullptr;
            hr = actions->get_Item(1, &action);
            if (SUCCEEDED(hr)) {
              IExecAction* exec = nullptr;
              hr = action->QueryInterface(IID_IExecAction, (void**)&exec);
              if (SUCCEEDED(hr)) {
                BSTR task_path_bstr = nullptr;
                hr = exec->get_Path(&task_path_bstr);
                if (SUCCEEDED(hr)) {
                  task_path = wstring(task_path_bstr, SysStringLen(task_path_bstr)); // task_path complete
                } // exec->get_Path(&task_path_bstr)
              } // action->QueryInterface(IID_IExecAction, (void**)&exec)
            } // actions->get_Item(1, &action)
          } // def->get_Actions(&actions)

        } // task->get_Definition(&def)

      } // task->get_Name(&task_name_bstr)

    } // task_collection->get_Item(_variant_t(i + 1), &task)
    size_t replace_use;
    while ((replace_use = task_path.find(L"\"")) != wstring::npos) task_path.replace(replace_use, 1, L"");
    Util::ToFullPath(task_path);
    DWORD verify = PeSignatureVerifier::CheckFileSignature(task_path);
    tasks.push_back(task_t(task_name, task_desc, task_path, verify));
  } // for loop
}