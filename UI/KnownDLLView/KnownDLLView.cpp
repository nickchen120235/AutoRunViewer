#include "KnownDLLView.h"
#include <lib/KnownDLL.h>

KnownDLLView::KnownDLLView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    // prepare the view
    this->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    this->tableWidget->verticalHeader()->hide();

    // get data
    vector<KnownDLL::knowndll_t> dll = KnownDLL::GetDLL();
    this->tableWidget->setRowCount(dll.size());
    for (int i = 0; i < dll.size(); ++i) {
      wstring e, im; DWORD v;
      std::tie(e, v, im) = dll[i];
      QString entry = QString::fromStdWString(e);
      QString verified;
      switch (v) {
      case ERROR_SUCCESS: verified = "Yes"; break;
      case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
      default: verified = "Unknown";
      }
      QString impa = QString::fromStdWString(im);
      this->tableWidget->setItem(i, 0, new QTableWidgetItem(entry));
      this->tableWidget->setItem(i, 1, new QTableWidgetItem(verified));
      this->tableWidget->setItem(i, 2, new QTableWidgetItem(impa));
    }

    // adjust column width
    this->tableWidget->resizeColumnToContents(0);
}

KnownDLLView::~KnownDLLView()
{
}
