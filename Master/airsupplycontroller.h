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
    explicit AirSupplyController(Schedule &schedule, QObject *parent = nullptr);
    void UpdateAirSupply(const bool OpenorClose, const QString &RoomID);

private:
    static constexpr int kDelayMs = 1;
    Schedule &_schedule;
    Rooms &_rooms;
    QTimer _timer;
    std::deque<std::pair<bool, QString>> _delayed_data;

private slots:
    void updateSupplyDelayed();
    void StartTimer();
    void StopTimer();
signals:
    void StartTimerFromAnotherThread();
    void StopTimerFromAnotherThread();
};

#endif // AIRSUPPLYCONTROLLER_H
