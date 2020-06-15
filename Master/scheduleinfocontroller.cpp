#include "scheduleinfocontroller.h"

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
        _rooms.delRoomIfExists(RoomID);
    }
    return res;
}
