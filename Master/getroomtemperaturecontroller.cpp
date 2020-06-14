#include "getroomtemperaturecontroller.h"

GetRoomTemperatureController::GetRoomTemperatureController(QObject *parent) : QObject(parent)
{

}

double GetRoomTemperatureController::Get(const QString &RoomID)
{
    GetRoomTemperatureRequest getroomtemperaturerequest(RoomID);
    auto [error, degree] = getroomtemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "GetRoomTemperatureController error";
        qDebug() << error.err_str;
    }
    return degree;
}
