#include "AutoRunViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoRunViewer w;
    w.show();
    return a.exec();
}
