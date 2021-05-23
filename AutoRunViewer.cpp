#include "AutoRunViewer.h"

#include "UI/ServiceView/ServiceView.h"
#include "UI/DriverView/DriverView.h"
#include "UI/TaskView/TaskView.h"

AutoRunViewer::AutoRunViewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Service tab
    ServiceView* ser = new ServiceView(ui.serviceTab);
    ui.serviceTab->layout()->addWidget(ser);

    DriverView* drv = new DriverView(ui.driverTab);
    ui.driverTab->layout()->addWidget(drv);

    TaskView* task = new TaskView(ui.taskTab);
    ui.taskTab->layout()->addWidget(task);
}
