#ifndef GETROOMTEMPERATURECONTROLLER_H
#define GETROOMTEMPERATURECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <tuple>
#include <QString>
#include <QTimer>
#include <vector>

#include "common.h"
#include "requests.h"
#include "global.h"
#include "schedule.h"

class GetRoomTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit GetRoomTemperatureController(Schedule &schedule, QObject *parent = nullptr);
    double Get(const QString &RoomID);

private:
    QTimer _timer;
    Rooms &_rooms;
    Schedule &_schedule;

private slots:
    void GetALL();

};

#endif // GETROOMTEMPERATURECONTROLLER_H
