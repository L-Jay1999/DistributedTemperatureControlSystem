#include "setspeedcontroller.h"

bool SetSpeedController::Set()
{
    SetSpeedRequest *setspeedrequest = new SetSpeedRequest(_RoomID, _level);
    bool result = setspeedrequest->Send();
    delete setspeedrequest;
    return result;
}
