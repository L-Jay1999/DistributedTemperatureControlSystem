#include "usersetspeedcontroller.h"

UserSetSpeedController::UserSetSpeedController(QObject *parent)
     : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_SPEED, this);
}

bool UserSetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
    qDebug() << RoomID << (int)level << "set speed request";
     _rooms.SetSpeed(RoomID, level);
    return true;
}
