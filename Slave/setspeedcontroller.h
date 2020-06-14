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
    explicit SetSpeedController(QObject *parent = nullptr, const QString &RoomID = "", const SpeedLevel level = SpeedLevel::LOW);
    bool Set();

private:
    QString _RoomID;
    SpeedLevel _level;

signals:
    void AddTextSpeed(QString s);
};

#endif // SETSPEEDCONTROLLER_H
