#include "useandcostcontrollermaster.h"

UseAndCostControllerMaster::UseAndCostControllerMaster(QObject *parent)
    : QObject(parent) //, _rooms(getRooms())
{
//    _timer = new QTimer(this);
//    connect(_timer, SIGNAL(timeout()), this, SLOT(SendALL()));
//    _timer->start(15000);
}

bool UseAndCostControllerMaster::Send(const double use, const double cost, const QString &RoomID)
{
    UseAndCostRequest useandcostrequest(use, cost, RoomID);
    auto [error, res] = useandcostrequest.Send();
    if(error.hasError()){
        qDebug() << "UseandCostControllerMaster error";
        qDebug() << error.err_str;
    }
    return res;
}

//void UseAndCostControllerMaster::SendALL()
//{

//}
