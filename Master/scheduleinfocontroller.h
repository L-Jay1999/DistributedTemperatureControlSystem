#ifndef SCHEDULEINFOCONTROLLER_H
#define SCHEDULEINFOCONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>
#include <QString>

#include "common.h"
#include "requests.h"

class ScheduleInfoController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleInfoController(QObject *parent = nullptr);
    bool Send(const bool is_in_queue, const QString &RoomID);

signals:

};

#endif // SCHEDULEINFOCONTROLLER_H
