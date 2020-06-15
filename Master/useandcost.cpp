#include "useandcost.h"

UseAndCost::UseAndCost(QObject *parent) : QObject(parent), _rooms(getRooms())
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(UpdateUseandCost()));
    _useandcostcontroller = new UseAndCostControllerMaster(this);
}

void UseAndCost::Start(const QString &RoomID)
{
    qDebug() << "use and cost start" << RoomID;
    _timer->start(_interval);
    _RoomID = RoomID;
    if(_rooms.hasRoom(_RoomID))
        _UserID = _rooms.getRoom(_RoomID).id;
    _start_time = QDateTime::currentDateTime();
    _init_temperature =getRooms().getRoom(RoomID).config.getCurTemperature();
}

double UseAndCost::UseandCostfromStart(struct StatPayload &sp)
{
    qDebug() << "use and cost end";
    qDebug() << _this_use << _this_cost;
    _timer->stop();
    auto [res, use, cost] = _db.getUseAndCost(_RoomID, _UserID);
    _db.updateUseAndCost(_RoomID, _UserID, use + _this_use, cost + _this_cost);
    _useandcostcontroller->Send(_this_use, _this_cost, _RoomID);

    sp.room_id = _RoomID;
    sp.start_time = _start_time;
    sp.end_time = QDateTime::currentDateTime();
    sp.init_temperature = _init_temperature;
    sp.end_temperature = getRooms().getRoom(RoomID).config.getCurTemperature();
    sp.speed_level = getRooms().getRoom(RoomID).config.getLevel();
    sp.cost = _this_cost;

    return _this_use;
}

void UseAndCost::UpdateUseandCost()
{
    int speed = (int)_rooms.getRoom(_RoomID).config.getLevel();
    double P = 1.0;
    switch (speed) {
    case 0:
        P = 0.8;
        break;
    case 1:
        P = 1.0;
        break;
    case 2:
        P = 1.2;
        break;
    default:
        P = 1.0;
        break;
    }
    _this_use += P * _interval / 60000;
    _this_cost += _this_use * 5.0;
//    _useandcostcontroller->Send(_this_use, _this_cost, _RoomID);
}
