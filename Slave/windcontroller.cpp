#include "windcontroller.h"

bool WindController::Send()
{
    WindRequest windrequest(_RoomID, _open);
    bool result = windrequest.Send();
    return result;
}
