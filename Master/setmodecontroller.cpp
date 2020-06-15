#include "setmodecontroller.h"

SetModeController::SetModeController(QObject *parent) : QObject(parent), _rooms(getRooms())
{

}

bool SetModeController::Set(const WorkingMode mode, const QString &RoomID, const double default_degree)
{
    SetModeRequest setmoderequest(mode, RoomID, default_degree);
    auto [error, res] = setmoderequest.Send();
    if(error.hasError()){
        qDebug() << "SetModeController error";
        qDebug() << error.err_str;
    }
    return res;
}
