#include "shutdowncontroller.h"

bool ShutDownController::ShutDown()
{
    ShutDownRequest shutdownrequest(_RoomID);
    auto [error, result] = shutdownrequest.Send();
    if(!result){
        qDebug() << "shutdowncontroller error:";
        qDebug() << error.err_str;
    }
    return result;
}
