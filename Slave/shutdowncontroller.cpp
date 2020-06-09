#include "shutdowncontroller.h"

bool ShutDownController::ShutDown()
{
    ShutDownRequest *shutdownrequest = new ShutDownRequest(_RoomID);
    return shutdownrequest->Send();
}
