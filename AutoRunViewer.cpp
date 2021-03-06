#include "AutoRunViewer.h"

#include "UI/LogonView/LogonView.h"
#include "UI/ServiceView/ServiceView.h"
#include "UI/DriverView/DriverView.h"
#include "UI/TaskView/TaskView.h"
#include "UI/KnownDLLView/KnownDLLView.h"

AutoRunViewer::AutoRunViewer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    LogonView* lgn = new LogonView(ui.logonTab);
    ui.logonTab->layout()->addWidget(lgn);

    ServiceView* ser = new ServiceView(ui.serviceTab);
    ui.serviceTab->layout()->addWidget(ser);

    DriverView* drv = new DriverView(ui.driverTab);
    ui.driverTab->layout()->addWidget(drv);

    TaskView* task = new TaskView(ui.taskTab);
    ui.taskTab->layout()->addWidget(task);

    KnownDLLView* dll = new KnownDLLView(ui.dllTab);
    ui.dllTab->layout()->addWidget(dll);
}
