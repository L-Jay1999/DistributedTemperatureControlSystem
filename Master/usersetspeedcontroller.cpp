#include "usersetspeedcontroller.h"

UserSetSpeedController::UserSetSpeedController(QObject *parent, Schedule *schedule)
     : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_SPEED, this);
    _rooms = getRooms();
}

bool UserSetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
//    _schedule->SetSpeed(RoomID, level);
    _rooms.SetSpeed(RoomID, level);
    return true;
}
