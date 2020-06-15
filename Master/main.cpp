#include "standbywidget.h"
#include <QApplication>

#include "../CommonLib/common.h"
#include "userlogincontroller.h"
#include "usersetspeedcontroller.h"
#include "usersettemperaturecontroller.h"
#include "usershutdowncontroller.h"
#include "getroomtemperaturecontroller.h"
#include "schedule.h"
#include "useandcost.h"


int main(int argc, char *argv[])
{
    Config::setUserType(Config::UserType::MASTER);

    QApplication a(argc, argv);
    std::map<QString, UseAndCost*> useandcost;
    Schedule schedule(this,useandcost);
    UserLoginController login_controller;
    UserSetSpeedController speed_controller(this,useandcost);
    UserShutDownController shutdowncontroller;
    UserSetTemperatureController tempcontroller;
    GetRoomTemperatureController roomcontroller;
    StandbyWidget sw;
    sw.show();
    return a.exec();
}
