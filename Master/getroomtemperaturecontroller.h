#ifndef GETROOMTEMPERATURECONTROLLER_H
#define GETROOMTEMPERATURECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <tuple>
#include <QString>
#include <QTimer>
#include <vector>

#include "common.h"
#include "requests.h"
#include "global.h"

class GetRoomTemperatureController : public QObject
{
    Q_OBJECT
public:
    explicit GetRoomTemperatureController(QObject *parent = nullptr);
    double Get(const QString &RoomID);

private:
    QTimer *_timer;
    Rooms _rooms;

private slots:
    void GetALL();

};

#endif // GETROOMTEMPERATURECONTROLLER_H
