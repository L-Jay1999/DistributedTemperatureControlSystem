#include "settemperaturecontroller.h"

bool SetTemperatureController::Set()
{
    SetTemperatureRequest *settemperaturerequest = new SetTemperatureRequest(_RoomID, _degree);
    bool result = settemperaturerequest->Send();
    delete settemperaturerequest;
    return result;
}
