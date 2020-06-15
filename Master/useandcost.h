#ifndef USEANDCOST_H
#define USEANDCOST_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <tuple>

#include "common.h"
#include "useandcostcontrollermaster.h"
#include "dbaccess.h"
#include "global.h"

class UseAndCost : public QObject
{
    Q_OBJECT
public:
    explicit UseAndCost(QObject *parent = nullptr);
    void Start(const QString &RoomID);
    double UseandCostfromStart();

private:
    double _this_use;
    double _this_cost;
    const double _interval = 1000;
    QTimer *_timer;
    Rooms _rooms;
    QString _RoomID;
    QString _UserID;
    UseAndCostControllerMaster *_useandcostcontroller;
    DBAccess _db;

private slots:
    void UpdateUseandCost();

};

#endif // USEANDCOST_H
