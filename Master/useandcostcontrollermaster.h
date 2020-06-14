#ifndef USEANDCOSTCONTROLLERMASTER_H
#define USEANDCOSTCONTROLLERMASTER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "common.h"
#include "requests.h"

class UseAndCostControllerMaster : public QObject
{
    Q_OBJECT
public:
    explicit UseAndCostControllerMaster(QObject *parent = nullptr);
    bool Send(const double use, const double cost, const QString &RoomID);

signals:

};

#endif // USEANDCOSTCONTROLLERMASTER_H
