#include "getroomtemperaturecontroller.h"

#include <QMessageBox>

GetRoomTemperatureController::GetRoomTemperatureController(Schedule &schedule, QObject *parent)
    : QObject(parent), _timer(QTimer(this)), _rooms(getRooms()), _schedule(schedule)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(GetALL()));
    _timer.start(3000);
}

double GetRoomTemperatureController::Get(const QString &RoomID)
{
    GetRoomTemperatureRequest getroomtemperaturerequest(RoomID);
    auto [error, degree] = getroomtemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "GetRoomTemperatureController error";
        qDebug() << error.err_str;
        QMessageBox *err_box = new QMessageBox(QMessageBox::Warning, "获取温度失败", QString("无法连接到房间 %1").arg(RoomID), QMessageBox::Ok);
        err_box->show();
        _schedule.delRoom(RoomID);
        _rooms.delRoomIfExists(RoomID);
        degree = -1.0; // indicate room has been deleted
    }
    return degree;
}

void GetRoomTemperatureController::GetALL()
{
    std::vector<QString> res = _rooms.getRoomIDs();
    for(auto i : res){
        double degree = Get(i);
        if (degree > 0)
            _rooms.getRoom(i).config.setCurTemperature(degree);
    }
}
