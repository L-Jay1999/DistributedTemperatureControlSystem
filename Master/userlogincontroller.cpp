#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent)
     : QObject(parent)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
    _rooms = getRooms();
}

