#ifndef USEANDCOSTCONTROLLERMASTER_H
#define USEANDCOSTCONTROLLERMASTER_H

#include <QObject>
#include <QDebug>
#include <QString>
//#include <QTimer>

#include "common.h"
#include "requests.h"
//#include "global.h"

class UseAndCostControllerMaster : public QObject
{
    Q_OBJECT
public:
    explicit UseAndCostControllerMaster(QObject *parent = nullptr);
    bool Send(const double use, const double cost, const QString &RoomID);

//private:
//    QTimer *_timer;
//    Rooms _rooms;

//private slots:
//    void SendALL();

signals:

};

#endif // USEANDCOSTCONTROLLERMASTER_H
