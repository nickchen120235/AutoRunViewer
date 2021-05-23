#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutoRunViewer.h"

class AutoRunViewer : public QMainWindow
{
    Q_OBJECT

public:
    AutoRunViewer(QWidget *parent = Q_NULLPTR);

private:
    Ui::AutoRunViewerClass ui;
};
