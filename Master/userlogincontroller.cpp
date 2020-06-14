#include "userlogincontroller.h"

UserLoginController::UserLoginController(QObject *parent, Schedule *schedule)
     : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::LOGIN, this);
    _rooms = getRooms();
}

bool UserLoginController::UserLogin(const QString &UserID, const QString &RoomID)
{
    if(!_db.isConnected())
        return false;
    if(_db.hasUser(RoomID, UserID)){
        auto [res, use, cost] = _db.getUseAndCost(RoomID, UserID);
        UseAndCostRequest useandcostrequest(use, cost);
        auto [error, result] = useandcostrequest.Send();
        if(error.hasError()){
            //重传
            qDebug() << "UserLoginController error";
            qDebug() << error.err_str;
            auto [error, result] = useandcostrequest.Send();
            if(error.hasError()){
                return false;
            }
            else{
                _rooms.addRoom(RoomID);
                return true;
            }
        }
        else{
            _rooms.addRoom(RoomID);
            return true;
        }
    }
    return false;
}
