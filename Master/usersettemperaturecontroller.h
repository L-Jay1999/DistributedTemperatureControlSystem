#ifndef USERSETTEMPERATURECONTROLLER_H
#define USERSETTEMPERATURECONTROLLER_H

#include <QObject>

#include "common.h"
#include "schedule.h"
#include "global.h"

class UserSetTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit UserSetTemperatureController(QObject *parent = nullptr, Schedule *schedule = nullptr);
    bool Set(const QString &RoomID, const double degree);

private:
    Schedule *_schedule;
    Rooms _rooms;

signals:

};

#endif // USERSETTEMPERATURECONTROLLER_H
