#ifndef SHUTDOWNCONTROLLER_H
#define SHUTDOWNCONTROLLER_H
#include <QString>

#include "requests.h"

class ShutDownController
{
public:
    ShutDownController() = delete;
    ShutDownController(const QString &RoomID) : _RoomID(RoomID) {}
    bool ShutDown();
private:
    QString _RoomID;
};

#endif // SHUTDOWNCONTROLLER_H
