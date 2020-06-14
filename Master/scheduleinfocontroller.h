#ifndef SCHEDULEINFOCONTROLLER_H
#define SCHEDULEINFOCONTROLLER_H

#include <QObject>
#include <tuple>
#include <QDebug>

#include "common.h"
#include "requests.h"

class ScheduleInfoController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleInfoController(QObject *parent = nullptr);
    bool Send(bool is_in_queue);

signals:

};

#endif // SCHEDULEINFOCONTROLLER_H
