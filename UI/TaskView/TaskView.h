#pragma once

#include <QWidget>
#include "ui_TaskView.h"

class TaskView : public QWidget, public Ui::TaskView
{
    Q_OBJECT

public:
    TaskView(QWidget *parent = Q_NULLPTR);
    ~TaskView();
};
