#include "usersetspeedcontroller.h"

UserSetSpeedController::UserSetSpeedController(QObject *parent)
     : QObject(parent)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_SPEED, this);
    _rooms = getRooms();
}

bool UserSetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
    qDebug() << RoomID << (int)level << "set speed request";
     _rooms.SetSpeed(RoomID, level);
    return true;
}
