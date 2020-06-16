#include "scheduleinfocontroller.h"
#include <QMessageBox>


ScheduleInfoController::ScheduleInfoController(QObject *parent) : QObject(parent), _rooms(getRooms())
{

}

bool ScheduleInfoController::Send(const bool is_in_queue, const QString &RoomID)
{
    ScheduleInfoRequest scheduleinforequest(is_in_queue, RoomID);
    auto [error, res] = scheduleinforequest.Send();
    if(error.hasError()){
        qDebug() << "ScheduleInfoController error";
        qDebug() << error.err_str;
        QMessageBox *err_box = new QMessageBox(QMessageBox::Warning, "发送调度数据失败", QString("无法连接到房间 %1").arg(RoomID), QMessageBox::Ok);
        err_box->show();
        // _rooms.delRoomIfExists(RoomID);
    }
    return res;
}
