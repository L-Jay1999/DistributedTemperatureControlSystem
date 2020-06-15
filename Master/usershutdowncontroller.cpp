#include "usershutdowncontroller.h"

UserShutDownController::UserShutDownController(Schedule &schedule, QObject *parent)
    : QObject(parent), _rooms(getRooms()), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SHUTDOWN, this);
    connect(&_timer, &QTimer::timeout, this, &UserShutDownController::ShutDownDelayed);
}

bool UserShutDownController::ShutDown(const QString &RoomID)
{
    qDebug() << RoomID << "shutdown request";
    _timer.stop();
    _delayed_data.push_back(RoomID);
    _timer.start(kDelayMs);
    return true;
}

void UserShutDownController::ShutDownDelayed()
{
    _timer.stop();
    auto RoomID = _delayed_data.front();
    _delayed_data.pop_front();

    _schedule.delRoom(RoomID);
    _rooms.delRoomIfExists(RoomID);
    if (_delayed_data.size())
        _timer.start(kDelayMs);
}
