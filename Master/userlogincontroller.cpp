#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent, Schedule *schedule)
     : QObject(parent)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
    _rooms = getRooms();
}

