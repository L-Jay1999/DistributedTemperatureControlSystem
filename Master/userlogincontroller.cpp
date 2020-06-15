#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent)
     : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
}

