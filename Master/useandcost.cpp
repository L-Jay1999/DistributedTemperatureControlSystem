#include "useandcost.h"

UseAndCost::UseAndCost(QObject *parent) : QObject(parent), _rooms(getRooms()), _useandcostcontroller(this)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(UpdateUseandCost()));
}

void UseAndCost::Start(const QString &RoomID)
{
    qDebug() << "use and cost start" << RoomID;
    _timer.start(_interval);
    _RoomID = RoomID;
    if(_rooms.hasRoom(_RoomID))
        _UserID = _rooms.getRoom(_RoomID).id;
    _start_time = QDateTime::currentDateTime();
    _init_temperature =getRooms().getRoom(RoomID).config.getCurTemperature();
    // qDebug() << _RoomID << _UserID;
}

double UseAndCost::UseandCostfromStart(struct StatPayload &sp)
{
    DBAccess db;
    qDebug() << "use and cost end, " << _this_use << ", " << _this_cost;
    _timer.stop();
    auto [res, use, cost] = db.getUseAndCost(_RoomID, _UserID);
    db.updateUseAndCost(_RoomID, _UserID, use + _this_use, cost + _this_cost);
    sp.room_id = _RoomID;
    sp.start_time = _start_time;
    sp.end_time = QDateTime::currentDateTime();
    sp.init_temperature = _init_temperature;
    sp.end_temperature = getRooms().getRoom(_RoomID).config.getCurTemperature();
    sp.speed_level = getRooms().getRoom(_RoomID).config.getLevel();
    sp.cost = _this_cost;
    _useandcostcontroller.Send(use + _this_use, cost + _this_cost, _RoomID);
    return _this_cost;
}

void UseAndCost::UpdateUseandCost()
{
    if (!_rooms.hasRoom(_RoomID))
        return;
    double P = 1.0;
    switch (_rooms.getRoom(_RoomID).config.getLevel()) {
    case SpeedLevel::LOW:
        P = 0.8;
        break;
    case SpeedLevel::MID:
        P = 1.0;
        break;
    case SpeedLevel::HIGH:
        P = 1.2;
        break;
    default:
        P = 1.0;
        break;
    }
    _this_use += P * _interval / 60000;
    _this_cost = _this_use * 5.0;
    if (_count_down <= 0)
    {
        DBAccess db;
        auto [res, use, cost] = db.getUseAndCost(_RoomID, _UserID);
        _useandcostcontroller.Send(use + _this_use, cost + _this_cost, _RoomID);
        _count_down = 5;
    }
    else
        _count_down--;
    qDebug() << "update" << P << _this_use << _this_cost;
//    _useandcostcontroller->Send(_this_use, _this_cost, _RoomID);
}
