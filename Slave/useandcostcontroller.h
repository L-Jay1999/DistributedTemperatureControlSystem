#ifndef USEANDCOSTCONTROLLER_H
#define USEANDCOSTCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

#include "user.h"

class UseAndCostController : public QObject
{
    Q_OBJECT
public:
    explicit UseAndCostController(QObject *parent = nullptr);
    void setUseandCost(double use, double cost);
    void setUser(User *user);

private:
    User *_user;

signals:
    void UseandCostChanged();

public slots:
    void test();
};

#endif // USEANDCOSTCONTROLLER_H
