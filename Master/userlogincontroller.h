#ifndef USERLOGINCONTROLLER_H
#define USERLOGINCONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>

#include "global.h"
#include "common.h"
#include "dbaccess.h"
#include "requests.h"

class UserLoginController : public QObject
{
    Q_OBJECT
public:
    explicit UserLoginController(QObject *parent = nullptr);
    std::tuple<bool, WorkingMode, double> UserLogin(const QString &UserID, const QString &RoomID)
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


private:
    Rooms &_rooms;
    // DBAccess _db;
signals:

};

#endif // USERLOGINCONTROLLER_H
