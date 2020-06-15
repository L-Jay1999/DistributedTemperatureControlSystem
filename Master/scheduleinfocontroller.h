#ifndef SCHEDULEINFOCONTROLLER_H
#define SCHEDULEINFOCONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>
#include <QString>

#include "common.h"
#include "requests.h"
#include "global.h"

class ScheduleInfoController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleInfoController(QObject *parent = nullptr);
    bool Send(const bool is_in_queue, const QString &RoomID);

private:
    Rooms &_rooms;

signals:

};

#endif // SCHEDULEINFOCONTROLLER_H
