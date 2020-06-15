#include "airsupplycontroller.h"

AirSupplyController::AirSupplyController(QObject *parent, Schedule *schedule)
    : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST, this);
    _schedule = schedule;
    connect(&_timer, &QTimer::timeout, this, &AirSupplyController::updateSupplyDelayed);
}

void AirSupplyController::UpdateAirSupply(const bool OpenorClose, const QString &RoomID)
{
    qDebug() << "UpdateAirSupply" << RoomID;
    _delayed_data.push_back({OpenorClose, RoomID});
    _timer.start(kDelayMs);
}

void AirSupplyController::updateSupplyDelayed()
{
    _timer.stop();
    auto [OpenorClose, RoomID] = _delayed_data.front();
    _delayed_data.pop_front();
    if(OpenorClose)
    {
        _schedule->addRoom(_RoomID);
    }
    else
    {
        _schedule->delRoom(_RoomID);
    }
    if(_rooms.hasRoom(_RoomID))
    {
        _rooms.getRoom(_RoomID).has_wind = _openorclose;
    }
    if (_delayed_data.size())
        _timer.start(kDelayMs);
}
