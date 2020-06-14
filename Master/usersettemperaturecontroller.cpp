#include "usersettemperaturecontroller.h"

UserSetTemperatureController::UserSetTemperatureController(QObject *parent)
     : QObject(parent)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_TEMP, this);
    _rooms = getRooms();
}

bool UserSetTemperatureController::Set(const QString &RoomID, const double degree)
{
    qDebug() << RoomID << degree << "set temp request";
    _rooms.SetTemperature(RoomID, degree);
    return true;
}
