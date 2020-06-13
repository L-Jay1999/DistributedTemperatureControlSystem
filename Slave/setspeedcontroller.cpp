#include "setspeedcontroller.h"

bool SetSpeedController::Set()
{
    SetSpeedRequest setspeedrequest(_RoomID, _level);
    auto [error, result] = setspeedrequest.Send();
    if(!result){
        qDebug() << "setspeedcontroller error:";
        qDebug() << error.err_str;
    }
    return result;
}
