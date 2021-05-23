#include "DriverView.h"
#include <lib/Service.h>

DriverView::DriverView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    // prepare the view
    this->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    this->tableWidget->verticalHeader()->hide();

    // get data
    vector<Service::service_t> drv = Service::GetDrivers();
    this->tableWidget->setRowCount(drv.size());
    for (int i = 0; i < drv.size(); ++i) {
      wstring e, im;
      std::tie(e, std::ignore, im, std::ignore) = drv[i];
      QString entry = QString::fromStdWString(e);
      QString impa = QString::fromStdWString(im);
      this->tableWidget->setItem(i, 0, new QTableWidgetItem(entry));
      this->tableWidget->setItem(i, 1, new QTableWidgetItem(impa));
    }

    // adjust column width
    this->tableWidget->resizeColumnToContents(0);
}

DriverView::~DriverView()
{
}
