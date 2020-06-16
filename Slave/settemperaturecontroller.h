#ifndef SETTEMPERATURECONTROLLER_H
#define SETTEMPERATURECONTROLLER_H

#include <QString>
#include <tuple>
#include <QDebug>
#include <QObject>

#include "requests.h"

class SetTemperatureController : public QObject
{
    Q_OBJECT

public:
    SetTemperatureController() = delete;
    explicit SetTemperatureController(QObject *parent = nullptr);
    bool Set(const QString &RoomID, const double degree);

signals:
    void AddTextTemp(QString s);
    void ShutDown();
};

#endif // SETTEMPERATURECONTROLLER_H
