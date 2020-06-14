#ifndef GETTEMPERATURECONTROLLER_H
#define GETTEMPERATURECONTROLLER_H

#include <QObject>

#include "common.h"
#include "sensor.h"

class GetTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit GetTemperatureController(QObject *parent = nullptr, Sensor *sensor = new Sensor());
    double get();

private:
    Sensor *_sensor;
};

#endif // GETTEMPERATURECONTROLLER_H
