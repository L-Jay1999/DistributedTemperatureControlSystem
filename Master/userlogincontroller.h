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
        qDebug() << UserID << RoomID;
        if(!_db.isConnected())
            return {false, {}, {}};
        if(_db.hasUser(RoomID, UserID)){
            qDebug() << "login success";
            _rooms.addRoom(RoomID);
            return {true, getCurrentWorkingMode(), getDefaultWorkingTemperature()};
            // return {false, {}, {}};
        }
        return {false, {}, {}};
    }


private:
    Rooms &_rooms;
    DBAccess _db;
signals:

};

#endif // USERLOGINCONTROLLER_H
