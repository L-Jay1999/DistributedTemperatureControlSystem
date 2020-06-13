#include "useandcostcontroller.h"

UseAndCostController::UseAndCostController(QObject *parent) : QObject(parent)
{
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(test()));
//    timer->start(5000);
}

void UseAndCostController::setUseandCost(double use, double cost)
{
    _user->setCost(cost);
    _user->setUsage(use);
    emit UseandCostChanged();
}

void UseAndCostController::setUser(User *user)
{
    _user = user;
}

void UseAndCostController::test()
{
    qDebug() << "test";
    setUseandCost(_user->getUsage() + 1.0, _user->getCost() + 1.0);
}
