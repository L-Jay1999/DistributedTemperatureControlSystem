// #include "mainwindow.h"
// #include "userloginwidget.h"
#include "startupwindow.h"
#include "slavecontrolwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // UserLoginWidget u;
    // u.show();
    // StartUpWindow start_up_window;
    // start_up_window.show();
    SlaveControlWindow control_panel;
    control_panel.show();
    return a.exec();
}
