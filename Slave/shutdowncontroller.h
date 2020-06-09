#ifndef SHUTDOWNCONTROLLER_H
#define SHUTDOWNCONTROLLER_H
#include <QString>
#include <../CommonLib/requests.h>

class ShutDownController
{
public:
    ShutDownController() = delete;
    ShutDownController(QString RoomID) : _RoomID(RoomID) {}
    bool ShutDown();
private:
    QString _RoomID;
};

#endif // SHUTDOWNCONTROLLER_H
