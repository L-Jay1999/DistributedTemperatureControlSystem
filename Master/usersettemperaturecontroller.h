#ifndef USERSETTEMPERATURECONTROLLER_H
#define USERSETTEMPERATURECONTROLLER_H

#include <QObject>

#include "common.h"
#include "global.h"

class UserSetTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit UserSetTemperatureController(QObject *parent = nullptr);
    bool Set(const QString &RoomID, const double degree);

private:
    Rooms _rooms;

signals:

};

#endif // USERSETTEMPERATURECONTROLLER_H
