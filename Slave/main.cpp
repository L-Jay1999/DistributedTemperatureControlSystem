//#include "mainwindow.h"
#include "userloginwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserLoginWidget u;
    u.show();
    return a.exec();
}
