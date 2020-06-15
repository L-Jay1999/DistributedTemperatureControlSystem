#include "usershutdowncontroller.h"

UserShutDownController::UserShutDownController(QObject *parent)
    : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SHUTDOWN, this);
}

bool UserShutDownController::ShutDown(const QString &RoomID)
{
    qDebug() << RoomID << "shutdown request";
    _rooms.delRoomIfExists(RoomID);
    return true;
}
