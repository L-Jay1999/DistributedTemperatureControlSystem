#ifndef SETMODECONTROLLER_H
#define SETMODECONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>
#include <QString>

#include "requests.h"
#include "common.h"
#include "global.h"

class SetModeController : public QObject
{
    Q_OBJECT
public:
    explicit SetModeController(QObject *parent = nullptr);
    bool Set(const WorkingMode mode, const QString &RoomID, const double default_degree);

private:
    Rooms &_rooms;

signals:

};

#endif // SETMODECONTROLLER_H
