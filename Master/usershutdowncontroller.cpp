#include "usershutdowncontroller.h"

UserShutDownController::UserShutDownController(QObject *parent, Schedule *schedule)
    : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SHUTDOWN, this);
    _rooms = getRooms();
}

bool UserShutDownController::ShutDown(const QString &RoomID)
{
    _rooms.delRoomIfExists(RoomID);
    return true;
}
