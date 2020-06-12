#ifndef WINDCONTROLLER_H
#define WINDCONTROLLER_H

#include <QString>

#include "../CommonLib/requests.h"

class WindController
{
public:
    WindController() = delete;
    WindController(const bool open, const QString &RoomID) : _open(open), _RoomID(RoomID) {}
    bool Send();

private:
    bool _open;
    QString _RoomID;
};

#endif // WINDCONTROLLER_H
