#pragma once

#include <QWidget>
#include "ui_ServiceView.h"

class ServiceView : public QWidget, public Ui::ServiceView
{
    Q_OBJECT

public:
    ServiceView(QWidget *parent = Q_NULLPTR);
    ~ServiceView();
};
