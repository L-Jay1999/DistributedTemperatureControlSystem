#ifndef AIRSUPPLYCONTROLLER_H
#define AIRSUPPLYCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <deque>

#include "schedule.h"
#include "common.h"
#include "global.h"


class Schedule;
class AirSupplyController : public QObject
{
    Q_OBJECT

public:
    explicit AirSupplyController(QObject *parent = nullptr, Schedule *schedule = nullptr);
    void UpdateAirSupply(bool OpenorClose, const QString &RoomID);

private:
    static constexpr int kDelayMs = 250;
    Schedule *_schedule;
    Rooms &_rooms;
    QTimer _timer;
    std::deque<std::pair<bool, QString>> _delayed_data;
private slots:
    void updateSupplyDelayed();

signals:

public slots:
};

#endif // AIRSUPPLYCONTROLLER_H
