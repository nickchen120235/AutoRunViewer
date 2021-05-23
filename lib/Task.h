#pragma once

#define _WIN32_DCOM
#include <vector>
#include <string>
#include <tuple>
#include <deque>
#include <Windows.h>
#include <comdef.h>
#include <taskschd.h>
#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")

using std::wstring;
using std::vector;
using std::tuple;
using std::deque;

namespace Task {
  // Entry, Description, ImagePath
  typedef tuple<wstring, wstring, wstring> task_t;

  vector<task_t> GetTasks();
  void _walk_folders(vector<task_t>&, ITaskFolder*, deque<wstring>&);
  void _walk_tasks(vector<task_t>&, ITaskFolder*, deque<wstring>&);
};