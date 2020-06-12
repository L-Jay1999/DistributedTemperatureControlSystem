#ifndef MANAGERLOGINCONTROLLER_H
#define MANAGERLOGINCONTROLLER_H

#include <QString>
#include <tuple>
#include "../CommonLib/requests.h"

class ManagerLoginController
{
public:
    ManagerLoginController() = delete;
    ManagerLoginController(const QString &Account, const QString &Password, const quint16 &port)
        : _Account(Account), _Password(Password), _port(port)
    {}
    std::tuple<bool, QString> ManagerLogin();


private:
    QString _Account;
    QString _Password;
    QString _port;
    bool CheckArgs();

};

#endif // MANAGERLOGINCONTROLLER_H
