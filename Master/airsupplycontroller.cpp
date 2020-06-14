#include "airsupplycontroller.h"

AirSupplyController::AirSupplyController(QObject *parent)
    : QObject(parent)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST, this);
    _schedule = (Schedule *)parent;
    _rooms = getRooms();
}

void AirSupplyController::UpdateAirSupply(bool OpenorClose, const QString &RoomID)
{
    if(OpenorClose){
        _schedule->addRoom(RoomID);

    }
    else{
        _schedule->delRoom(RoomID);
    }
    if(_rooms.hasRoom(RoomID)){
        _rooms.getRoom(RoomID).has_wind = OpenorClose;
    }
}
