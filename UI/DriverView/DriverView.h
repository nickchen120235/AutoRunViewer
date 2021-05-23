#pragma once

#include <QWidget>
#include "ui_DriverView.h"

class DriverView : public QWidget, public Ui::DriverView
{
    Q_OBJECT

public:
    DriverView(QWidget *parent = Q_NULLPTR);
    ~DriverView();
};
