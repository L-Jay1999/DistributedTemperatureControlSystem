#ifndef SETSPEEDCONTROLLER_H
#define SETSPEEDCONTROLLER_H
#include <QString>

#include "../CommonLib/common.h"
#include "../CommonLib/requests.h"

class SetSpeedController
{
public:
    SetSpeedController() = delete;
    SetSpeedController(const QString &RoomID, const SpeedLevel level) : _RoomID(RoomID), _level(level) {}
    bool Set();

private:
    QString _RoomID;
    SpeedLevel _level;
};

#endif // SETSPEEDCONTROLLER_H
