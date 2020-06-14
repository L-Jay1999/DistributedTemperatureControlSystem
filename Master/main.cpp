#include "standbywidget.h"
#include <QApplication>

#include "../CommonLib/common.h"
#include "userlogincontroller.h"


int main(int argc, char *argv[])
{
    Config::setUserType(Config::UserType::MASTER);

    QApplication a(argc, argv);
    UserLoginController login_controller;
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
