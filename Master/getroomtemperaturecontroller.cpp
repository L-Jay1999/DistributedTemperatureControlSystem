#include "getroomtemperaturecontroller.h"

GetRoomTemperatureController::GetRoomTemperatureController(QObject *parent) : QObject(parent)
{

}

double GetRoomTemperatureController::Get()
{
    GetRoomTemperatureRequest getroomtemperaturerequest;
    auto [error, degree] = getroomtemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "GetRoomTemperatureController error";
        qDebug() << error.err_str;
    }
    return degree;
}
