#include "useandcostcontroller.h"

UseAndCostController::UseAndCostController(QObject *parent, User *user) : QObject(parent), _user(user)
{
    Config::setSlaveControllerPointer(Config::SlaveControllerType::USE_COST, this);
    connect(this, SIGNAL(UseandCostChanged()), parent, SLOT(GetUseandCost()));
}

void UseAndCostController::setUseandCost(double use, double cost)
{
    _user->setCost(cost);
    _user->setUsage(use);
    emit UseandCostChanged();
}

void UseAndCostController::test()
{
    qDebug() << "test";
    setUseandCost(_user->getUsage() + 1.0, _user->getCost() + 1.0);
}
