#ifndef AIRSUPPLYCONTROLLER_H
#define AIRSUPPLYCONTROLLER_H

#include <QObject>

#include "schedule.h"
#include "common.h"
#include "global.h"

class Schedule;
class AirSupplyController : public QObject
{
    Q_OBJECT

public:
    explicit AirSupplyController(QObject *parent = nullptr);
    void UpdateAirSupply(bool OpenorClose, const QString &RoomID);

private:
    Schedule *_schedule;
    Rooms _rooms;

signals:

public slots:
};

#endif // AIRSUPPLYCONTROLLER_H
