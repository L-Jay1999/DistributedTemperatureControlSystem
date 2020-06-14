#ifndef USERSETSPEEDCONTROLLER_H
#define USERSETSPEEDCONTROLLER_H

#include <QObject>

#include "common.h"
#include "schedule.h"
#include "global.h"

class UserSetSpeedController : public QObject
{
    Q_OBJECT
public:
    explicit UserSetSpeedController(QObject *parent = nullptr);
    bool Set(const QString &RoomID, const SpeedLevel level);

private:
    Rooms _rooms;

signals:

};

#endif // USERSETSPEEDCONTROLLER_H
