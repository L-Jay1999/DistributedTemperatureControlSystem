#include "useandcost.h"

UseAndCost::UseAndCost(QObject *parent) : QObject(parent)
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(UpdateUseandCost()));
    _rooms = getRooms();
    _useandcostcontroller = new UseAndCostControllerMaster(this);
}

void UseAndCost::Start(const QString &RoomID)
{
    _timer->start(_interval);
    _RoomID = RoomID;
    if(_rooms.hasRoom(_RoomID))
        _UserID = _rooms.getRoom(_RoomID).id;
}

double UseAndCost::UseandCostfromStart()
{
    _timer->stop();
    auto [res, use, cost] = _db.getUseAndCost(_RoomID, _UserID);
    _db.updateUseAndCost(_RoomID, _UserID, use + _this_use, cost + _this_cost);
    _useandcostcontroller->Send(_this_use, _this_cost, _RoomID);
    return _this_use;
}

void UseAndCost::UpdateUseandCost()
{
    int speed = (int)_rooms.getRoom(_RoomID).config.getLevel() + 1;
    _this_use += speed * _interval / 1000;
    _this_cost = _this_use * 0.5;
    _useandcostcontroller->Send(_this_use, _this_cost, _RoomID);
}
