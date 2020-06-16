#include "getroomtemperaturecontroller.h"

GetRoomTemperatureController::GetRoomTemperatureController(QObject *parent)
    : QObject(parent), _timer(QTimer(this)), _rooms(getRooms())
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
