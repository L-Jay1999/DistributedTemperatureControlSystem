#include "setmodecontroller.h"

SetModeController::SetModeController(QObject *parent) : QObject(parent)
{

}

bool SetModeController::Set(WorkingMode mode)
{
    SetModeRequest setmoderequest(mode);
    auto [error, res] = setmoderequest.Send();
    if(error.hasError()){
        qDebug() << "SetModeController error";
        qDebug() << error.err_str;
    }
    return res;
}
