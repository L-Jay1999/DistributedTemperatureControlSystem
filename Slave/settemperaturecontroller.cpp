#include "settemperaturecontroller.h"

bool SetTemperatureController::Set()
{
    SetTemperatureRequest settemperaturerequest(_RoomID, _degree);
    auto [error, result] = settemperaturerequest.Send();
    if(!result){
        qDebug() << "settemperaturecontroller error:";
        qDebug() << error.err_str;
    }
    return result;
}
