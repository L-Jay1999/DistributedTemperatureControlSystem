#include "gettemperaturecontroller.h"

GetTemperatureController::GetTemperatureController(QObject *parent, Sensor *sensor)
    : QObject(parent), _sensor(sensor)
{
    Config::setSlaveControllerPointer(Config::SlaveControllerType::GET_TEMPERATURE, this);
}

double GetTemperatureController::get()
{
    return _sensor->GetTemperature();
}
