#include "useandcostcontroller.h"

UseAndCostController::UseAndCostController(QObject *parent, User *user) : QObject(parent), _user(user)
{

}

void UseAndCostController::setUseandCost(double use, double cost)
{
    _user->setCost(cost);
    _user->setUsage(use);
    emit UseandCostChanged();
}

//void UseAndCostController::setUser(User *user)
//{
//    _user = user;
//}

void UseAndCostController::test()
{
    qDebug() << "test";
    setUseandCost(_user->getUsage() + 1.0, _user->getCost() + 1.0);
}
