#include "setmodecontroller.h"
#include <QMessageBox>


SetModeController::SetModeController(QObject *parent) : QObject(parent), _rooms(getRooms())
{

}

bool SetModeController::Set(const WorkingMode mode, const QString &RoomID, const double default_degree)
{
    SetModeRequest setmoderequest(mode, RoomID, default_degree);
    auto [error, res] = setmoderequest.Send();
    if(error.hasError()){
        qDebug() << error.err_str;
        QMessageBox *err_box = new QMessageBox(QMessageBox::Warning, "发送模式更改失败", QString("无法连接到房间 %1").arg(RoomID), QMessageBox::Ok);
        qDebug() << "SetModeController error";
        qDebug() << error.err_str;
    }
    return res;
}
