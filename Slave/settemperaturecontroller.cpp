#include "settemperaturecontroller.h"

bool SetTemperatureController::Set()
{
    SetTemperatureRequest settemperaturerequest(_RoomID, _degree);
    bool result = settemperaturerequest.Send();
    return result;
}
