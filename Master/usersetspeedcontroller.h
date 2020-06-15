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
    explicit UserSetSpeedController(std::map<QString, UseAndCost*> &u, QObject *parent = nullptr);
    bool Set(const QString &RoomID, const SpeedLevel level);

private:
    static constexpr int kDelayMs = 250;
    Rooms &_rooms;
    std::map<QString, UseAndCost*> &useandcost;
    QTimer _timer;
    std::deque<std::pair<QString, SpeedLevel>> _delayed_data;
private slots:
    void SetDelayed();
signals:

};

#endif // USERSETSPEEDCONTROLLER_H
