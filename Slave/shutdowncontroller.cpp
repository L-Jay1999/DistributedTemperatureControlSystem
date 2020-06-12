#include "shutdowncontroller.h"

bool ShutDownController::ShutDown()
{
    ShutDownRequest shutdownrequest(_RoomID);
    bool result = shutdownrequest.Send();
    return result;
}
