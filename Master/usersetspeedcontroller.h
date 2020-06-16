#ifndef USERSETSPEEDCONTROLLER_H
#define USERSETSPEEDCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <deque>

#include "common.h"
#include "schedule.h"
#include "global.h"
#include "useandcost.h"

class UserSetSpeedController : public QObject
{
    Q_OBJECT
public:
    explicit UserSetSpeedController(std::map<QString, std::shared_ptr<UseAndCost>> &u, QObject *parent = nullptr);
    bool Set(const QString &RoomID, const SpeedLevel level);

private:
    static constexpr int kDelayMs = 1;
    Rooms &_rooms;
    std::map<QString, std::shared_ptr<UseAndCost>> &useandcost;
    QTimer _timer;
    std::deque<std::pair<QString, SpeedLevel>> _delayed_data;
private slots:
    void SetDelayed();
    void StartTimer();
    void StopTimer();
signals:
    void StopTimerFromAnotherThread();
    void StartTimerFromAnotherThread();
};

#endif // USERSETSPEEDCONTROLLER_H
