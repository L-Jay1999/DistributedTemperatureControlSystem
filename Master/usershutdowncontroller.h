#ifndef USERSHUTDOWNCONTROLLER_H
#define USERSHUTDOWNCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <deque>

#include "common.h"
#include "global.h"
#include "schedule.h"

class UserShutDownController : public QObject
{
    Q_OBJECT
public:
    explicit UserShutDownController(Schedule &schedule, QObject *parent = nullptr);
    bool ShutDown(const QString &RoomID);

private:
    static constexpr int kDelayMs = 1;
    Rooms &_rooms;
    Schedule &_schedule;
    QTimer _timer;
    std::deque<QString> _delayed_data;
private slots:
    void ShutDownDelayed();
    void StartTimer();
    void StopTimer();
signals:
    void StartTimerFromAnotherThread();
    void StopTimerFromAnotherThread();
};

#endif // USERSHUTDOWNCONTROLLER_H
