#include "airsupplycontroller.h"

AirSupplyController::AirSupplyController(Schedule &schedule, QObject *parent)
    : QObject(parent), _rooms(getRooms()), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST, this);
    connect(&_timer, &QTimer::timeout, this, &AirSupplyController::updateSupplyDelayed);
    connect(this, &AirSupplyController::StartTimerFromAnotherThread,
            this, &AirSupplyController::StartTimer);
    connect(this, &AirSupplyController::StopTimerFromAnotherThread,
            this, &AirSupplyController::StopTimer);
}

void AirSupplyController::UpdateAirSupply(const bool OpenorClose, const QString &RoomID)
{
    qDebug() << "UpdateAirSupply" << RoomID;
    emit StopTimerFromAnotherThread();
    _delayed_data.push_back({OpenorClose, RoomID});
    emit StartTimerFromAnotherThread();
}

void AirSupplyController::updateSupplyDelayed()
{
    _timer.stop();
    auto [OpenorClose, RoomID] = _delayed_data.front();
    _delayed_data.pop_front();
    if (getRooms().hasRoom(RoomID))
    {
        if(OpenorClose)
            _schedule.addRoom(RoomID);
        else
            _schedule.delRoom(RoomID);
        if(_rooms.hasRoom(RoomID))
            _rooms.getRoom(RoomID).has_wind = OpenorClose;
    }
    else
    {
        // ERROR HANDLING
    }
    if (_delayed_data.size())
        _timer.start(kDelayMs);
}

void AirSupplyController::StartTimer()
{
    _timer.start();
}

void AirSupplyController::StopTimer()
{
    _timer.stop();
}
