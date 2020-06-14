#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent, Schedule *schedule)
     : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
    _rooms = getRooms();
}

