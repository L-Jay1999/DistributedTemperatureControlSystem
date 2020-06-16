#include "usershutdowncontroller.h"

UserShutDownController::UserShutDownController(Schedule &schedule, QObject *parent)
    : QObject(parent), _rooms(getRooms()), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SHUTDOWN, this);
    connect(&_timer, &QTimer::timeout, this, &UserShutDownController::ShutDownDelayed);
    connect(this, &UserShutDownController::StartTimerFromAnotherThread,
            this, &UserShutDownController::StartTimer);
    connect(this, &UserShutDownController::StopTimerFromAnotherThread,
            this, &UserShutDownController::StopTimer);
}

bool UserShutDownController::ShutDown(const QString &RoomID)
{
    qDebug() << RoomID << "shutdown request";
    emit StopTimerFromAnotherThread();
    _delayed_data.push_back(RoomID);
    emit StartTimerFromAnotherThread();
    return true;
}

void UserShutDownController::ShutDownDelayed()
{
    _timer.stop();
    auto RoomID = _delayed_data.front();
    _delayed_data.pop_front();

    _schedule.delRoom(RoomID);
    _rooms.delRoomIfExists(RoomID);
    DBAccess db;
    db.addRoomPowerStat(RoomID,false);
    if (_delayed_data.size())
        _timer.start(kDelayMs);
}

void UserShutDownController::StartTimer()
{
    _timer.start();
}

void UserShutDownController::StopTimer()
{
    _timer.stop();
}
