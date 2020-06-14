#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent, Schedule *schedule)
     : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
    _rooms = getRooms();
}

bool UserLoginController::UserLogin(const QString &UserID, const QString &RoomID)
{
    if(!_db.isConnected())
        return false;
    if(_db.hasUser(RoomID, UserID)){
        _rooms.addRoom(RoomID);
        return true;
    }
    return false;
}
