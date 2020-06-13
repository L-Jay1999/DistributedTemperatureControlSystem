#ifndef SETTEMPERATURECONTROLLER_H
#define SETTEMPERATURECONTROLLER_H

#include <QString>
#include <tuple>
#include <QDebug>

#include "requests.h"

class SetTemperatureController
{
public:
    SetTemperatureController() = delete;
    SetTemperatureController(const QString &RoomID, const double degree) : _RoomID(RoomID), _degree(degree) {}
    bool Set();

private:
    QString _RoomID;
    double _degree;
};

#endif // SETTEMPERATURECONTROLLER_H
