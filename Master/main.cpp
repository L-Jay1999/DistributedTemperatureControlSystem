#include "standbywidget.h"
#include <QApplication>

#include "../CommonLib/common.h"
#include "userlogincontroller.h"
#include "usersetspeedcontroller.h"
#include "usersettemperaturecontroller.h"
#include "usershutdowncontroller.h"


int main(int argc, char *argv[])
{
    Config::setUserType(Config::UserType::MASTER);

    QApplication a(argc, argv);
    UserLoginController login_controller;
    UserSetSpeedController speed_controller;
    UserShutDownController shutdowncontroller;
    UserSetTemperatureController tempcontroller;
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
