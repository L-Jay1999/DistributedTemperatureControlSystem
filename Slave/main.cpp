// #include "mainwindow.h"
// #include "userloginwidget.h"
#include "startupwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // UserLoginWidget u;
    // u.show();
    StartUpWindow start_up_window;
    start_up_window.show();
    return a.exec();
}
