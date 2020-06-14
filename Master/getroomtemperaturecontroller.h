#ifndef GETROOMTEMPERATURECONTROLLER_H
#define GETROOMTEMPERATURECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <tuple>
#include <QString>

#include "common.h"
#include "requests.h"

class GetRoomTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit GetRoomTemperatureController(QObject *parent = nullptr);
    double Get(const QString &RoomID);

signals:

};

#endif // GETROOMTEMPERATURECONTROLLER_H
