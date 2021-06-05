#pragma once

#include <QWidget>
#include "ui_KnownDLLView.h"

class KnownDLLView : public QWidget, public Ui::KnownDLLView
{
    Q_OBJECT

public:
    KnownDLLView(QWidget *parent = Q_NULLPTR);
    ~KnownDLLView();
};
