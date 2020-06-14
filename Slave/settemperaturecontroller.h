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
    explicit SetTemperatureController(QObject *parent = nullptr, const QString &RoomID = "", const double degree = 25.0);
    bool Set();

private:
    QString _RoomID;
    double _degree;

signals:
    void AddTextTemp(QString s);
};

#endif // SETTEMPERATURECONTROLLER_H
