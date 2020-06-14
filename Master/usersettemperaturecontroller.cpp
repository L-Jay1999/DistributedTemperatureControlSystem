#include "usersettemperaturecontroller.h"

UserSetTemperatureController::UserSetTemperatureController(QObject *parent, Schedule *schedule)
     : QObject(parent), _schedule(schedule)
{
    Config::setMasterControllerPointer(Config::MasterControllerType::SET_TEMP, this);
    _rooms = getRooms();
}

bool UserSetTemperatureController::Set(const QString &RoomID, const double degree)
{
//    _schedule->SetTemperature(RoomID, degree);
    _rooms.SetTemperature(RoomID, degree);
    return true;
}
