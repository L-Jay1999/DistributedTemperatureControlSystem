#include "shutdowncontroller.h"

bool ShutDownController::ShutDown()
{
    ShutDownRequest *shutdownrequest = new ShutDownRequest(_RoomID);
    bool result = shutdownrequest->Send();
    delete shutdownrequest;
    return result;
}
