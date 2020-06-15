#include "usersetspeedcontroller.h"

UserSetSpeedController::UserSetSpeedController(QObject *parent, std::map<QString, UseAndCost*> &u)
     : QObject(parent), _rooms(getRooms()), useandcost(u)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_SPEED, this);
}

bool UserSetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
    qDebug() << RoomID << (int)level << "set speed request";
    if(_rooms.getRoom(RoomID).config.getLevel() != level && _rooms.getRoom(RoomID).has_wind == true)//风速有改变，且正在送风
    {
        //构造详单，发送给数据库
        struct StatPayload sp;
        useandcost[RoomID]->UseandCostfromStart(sp);
        DBAccess db;
        if(db.addRoomRequestStat(sp) == false)
            return false;
        delete useandcost[RoomID];
        //改变风速，并记录一个新详单的开始
        _rooms.SetSpeed(RoomID, level);
        useandcost[RoomID] = new UseAndCost(this);
        useandcost[RoomID]->Start(RoomID);
        return true;

    }
    _rooms.SetSpeed(RoomID, level);
    return true;
}
