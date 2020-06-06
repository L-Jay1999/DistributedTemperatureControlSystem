//#include "mainwindow.h"
#include "userloginwidget.h"

#include <QApplication>
#include <QDebug>

#include "../CommonLib/common.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    UserLoginWidget u;
    u.show();
    return a.exec();
}
