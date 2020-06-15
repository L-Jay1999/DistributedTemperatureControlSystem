#include "usersettemperaturecontroller.h"

UserSetTemperatureController::UserSetTemperatureController(QObject *parent)
     : QObject(parent), _rooms(getRooms())
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_TEMP, this);
}

bool UserSetTemperatureController::Set(const QString &RoomID, const double degree)
{
    qDebug() << RoomID << degree << "set temp request";
    _rooms.SetTemperature(RoomID, degree);
    return true;
}
