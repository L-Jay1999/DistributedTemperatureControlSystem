#include "getroomtemperaturecontroller.h"

GetRoomTemperatureController::GetRoomTemperatureController(QObject *parent)
    : QObject(parent), _rooms(getRooms())
{

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(GetALL()));
    _timer->start(3000);
}

double GetRoomTemperatureController::Get(const QString &RoomID)
{
    GetRoomTemperatureRequest getroomtemperaturerequest(RoomID);
    auto [error, degree] = getroomtemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "GetRoomTemperatureController error";
        qDebug() << error.err_str;
    }
    return degree;
}

void GetRoomTemperatureController::GetALL()
{
    std::vector<QString> res = _rooms.getRoomIDs();
    for(auto i : res){
        double degree = Get(i);
        _rooms.getRoom(i).config.setCurTemperature(degree);
    }
}
