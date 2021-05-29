#pragma once

#include <QWidget>
#include "ui_LogonView.h"

class LogonView : public QWidget, public Ui::LogonView
{
    Q_OBJECT

public:
    LogonView(QWidget *parent = Q_NULLPTR);
    ~LogonView();
};
