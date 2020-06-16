#include "slavecontrolwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlaveControlWindow control_panel;
    control_panel.show();
    return a.exec();
}
