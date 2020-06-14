#ifndef USERSHUTDOWNCONTROLLER_H
#define USERSHUTDOWNCONTROLLER_H

#include <QObject>

#include "common.h"
#include "global.h"

class UserShutDownController : public QObject
{
    Q_OBJECT
public:
    explicit UserShutDownController(QObject *parent = nullptr);
    bool ShutDown(const QString &RoomID);

private:
    Rooms _rooms;

signals:

};

#endif // USERSHUTDOWNCONTROLLER_H
