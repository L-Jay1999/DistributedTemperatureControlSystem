#include "usersetspeedcontroller.h"

UserSetSpeedController::UserSetSpeedController(std::map<QString, UseAndCost*> &u, QObject *parent)
     : QObject(parent), _rooms(getRooms()), useandcost(u)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_SPEED, this);
    connect(&_timer, &QTimer::timeout, this, &UserSetSpeedController::SetDelayed);
}

bool UserSetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
    qDebug() << RoomID << (int)level << "set speed request";
    _timer.stop();
    _delayed_data.push_back({RoomID, level});
    _timer.start(kDelayMs);
    return true;
}

void UserSetSpeedController::SetDelayed()
{
    _timer.stop();
    auto [RoomID, level] = _delayed_data.front();
    _delayed_data.pop_front();
    int size = _delayed_data.size();

    if(_rooms.getRoom(RoomID).config.getLevel() != level && _rooms.getRoom(RoomID).has_wind == true)//风速有改变，且正在送风
    {
        //构造详单，发送给数据库
        struct StatPayload sp;
        useandcost[RoomID]->UseandCostfromStart(sp);
        DBAccess db;
        if(db.addRoomRequestStat(sp) == false)
        {
            delete useandcost[RoomID];
            if (size)
                _timer.start(kDelayMs);
            return;
        }
        delete useandcost[RoomID];
        //改变风速，并记录一个新详单的开始
        _rooms.SetSpeed(RoomID, level);
        useandcost[RoomID] = new UseAndCost(this);
        useandcost[RoomID]->Start(RoomID);
        if (size)
            _timer.start(kDelayMs);
        return;

    }
    _rooms.SetSpeed(RoomID, level);
    if (size)
        _timer.start(kDelayMs);
    return;
}
