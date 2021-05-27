#include "TaskView.h"
#include <lib/Task.h>

TaskView::TaskView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    // prepare the view
    this->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    this->tableWidget->verticalHeader()->hide();

    // get data
    vector<Task::task_t> tasks = Task::GetTasks();
    this->tableWidget->setRowCount(tasks.size());
    for (int i = 0; i < tasks.size(); ++i) {
      wstring e, d, im; DWORD v;
      std::tie(e, d, im, v) = tasks[i];
      QString entry = QString::fromStdWString(e);
      QString verified;
      switch (v) {
      case ERROR_SUCCESS: verified = "Yes"; break;
      case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
      default: verified = "Unknown";
      }
      QString impa = QString::fromStdWString(im);
      QString desc = QString::fromStdWString(d);
      this->tableWidget->setItem(i, 0, new QTableWidgetItem(entry));
      this->tableWidget->setItem(i, 1, new QTableWidgetItem(verified));
      this->tableWidget->setItem(i, 2, new QTableWidgetItem(impa));
      this->tableWidget->setItem(i, 3, new QTableWidgetItem(desc));
    }

    // adjust column width
    this->tableWidget->resizeColumnToContents(0);
    this->tableWidget->resizeColumnToContents(2);
}

TaskView::~TaskView()
{
}
