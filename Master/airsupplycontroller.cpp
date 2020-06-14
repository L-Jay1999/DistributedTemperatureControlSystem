#include "airsupplycontroller.h"

AirSupplyController::AirSupplyController(QObject *parent, Schedule *schedule)
    : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST, this);
}

void AirSupplyController::UpdateAirSupply(bool OpenorClose, const QString &RoomID)
{
    if(OpenorClose){
        _schedule->addRoom(RoomID);
    }
    else{
        _schedule->delRoom(RoomID);
    }
}
