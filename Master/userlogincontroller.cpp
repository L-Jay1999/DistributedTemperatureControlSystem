#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent)
     : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
}

std::tuple<bool, WorkingMode, double> UserLoginController::UserLogin(const QString &UserID, const QString &RoomID)
{
    DBAccess db;
    qDebug() << UserID << RoomID;
    if(!db.isConnected())
        return {false, {}, {}};
    if(db.hasUser(RoomID, UserID)){
        qDebug() << "login success";
        _rooms.addRoom(RoomID);
        _rooms.SetID(RoomID, UserID);
        db.addRoomPowerStat(RoomID,true);
        return {true, getCurrentWorkingMode(), getDefaultWorkingTemperature()};
        // return {false, {}, {}};
    }
    return {false, {}, {}};
}
