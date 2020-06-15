#include "airsupplycontroller.h"

AirSupplyController::AirSupplyController(QObject *parent, Schedule *schedule)
    : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST, this);
    _schedule = schedule;
}

void AirSupplyController::UpdateAirSupply(bool OpenorClose, const QString &RoomID)
{
    qDebug() << "UpdateAirSupply" << RoomID;
    if(OpenorClose)
    {
        _schedule->addRoom(RoomID);
    }
    else
    {
        _schedule->delRoom(RoomID);
    }
    if(_rooms.hasRoom(RoomID))
    {
        _rooms.getRoom(RoomID).has_wind = OpenorClose;
    }
}
