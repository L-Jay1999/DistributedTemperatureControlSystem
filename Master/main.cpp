#include "standbywidget.h"
#include <QApplication>

#include "../CommonLib/common.h"
#include "userlogincontroller.h"
#include "usersetspeedcontroller.h"
#include "usersettemperaturecontroller.h"
#include "usershutdowncontroller.h"
#include "getroomtemperaturecontroller.h"
#include "schedule.h"


int main(int argc, char *argv[])
{
    Config::setUserType(Config::UserType::MASTER);

    QApplication a(argc, argv);
    Schedule schedule;
    UserLoginController login_controller;
    UserSetSpeedController speed_controller;
    UserShutDownController shutdowncontroller;
    UserSetTemperatureController tempcontroller;
    GetRoomTemperatureController roomcontroller;
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
