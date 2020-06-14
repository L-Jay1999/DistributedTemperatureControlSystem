#ifndef AIRSUPPLYCONTROLLER_H
#define AIRSUPPLYCONTROLLER_H

#include <QObject>
#include <schedule.h>

#include "common.h"

class AirSupplyController : public QObject
{
    Q_OBJECT

public:
    explicit AirSupplyController(QObject *parent = nullptr, Schedule *schedule = nullptr);
    void UpdateAirSupply(bool OpenorClose, const QString &RoomID);

private:
    Schedule *_schedule;

signals:

public slots:
};

#endif // AIRSUPPLYCONTROLLER_H
