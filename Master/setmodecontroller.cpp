#include "setmodecontroller.h"

SetModeController::SetModeController(QObject *parent) : QObject(parent)
{

}

bool SetModeController::Set(const WorkingMode mode, const QString &RoomID)
{
    SetModeRequest setmoderequest(mode, RoomID);
    auto [error, res] = setmoderequest.Send();
    if(error.hasError()){
        qDebug() << "SetModeController error";
        qDebug() << error.err_str;
    }
    return res;
}
