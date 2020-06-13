#include "windcontroller.h"

bool WindController::Send()
{
    WindRequest windrequest(_RoomID, _open);
    auto [error, result] = windrequest.Send();
    if(!result){
        qDebug() << "windcontroller error:";
        qDebug() << error.err_str;
    }
    return result;
}
