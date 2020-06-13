#include "setspeedcontroller.h"

bool SetSpeedController::Set()
{
    SetSpeedRequest setspeedrequest(_RoomID, _level);
    bool result = setspeedrequest.Send();
    return result;
}
