#ifndef SETSPEEDCONTROLLER_H
#define SETSPEEDCONTROLLER_H

#include <QString>
#include <tuple>
#include <QDebug>
#include <QObject>

#include "common.h"
#include "requests.h"

class SetSpeedController : public QObject
{
    Q_OBJECT

public:
    SetSpeedController() = delete;
    explicit SetSpeedController(QObject *parent = nullptr);
    bool Set(const QString &RoomID, const SpeedLevel level);

signals:
    void AddTextSpeed(QString s);
    void ShutDown();
};

#endif // SETSPEEDCONTROLLER_H
