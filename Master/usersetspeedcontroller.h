#ifndef USERSETSPEEDCONTROLLER_H
#define USERSETSPEEDCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "common.h"
#include "schedule.h"
#include "global.h"

class UserSetSpeedController : public QObject
{
    Q_OBJECT
public:
    explicit UserSetSpeedController(QObject *parent = nullptr, std::map<QString, UseAndCost*> &u);
    bool Set(const QString &RoomID, const SpeedLevel level);

private:
    Rooms &_rooms;
    std::map<QString, UseAndCost*> &useandcost;
signals:

};

#endif // USERSETSPEEDCONTROLLER_H
