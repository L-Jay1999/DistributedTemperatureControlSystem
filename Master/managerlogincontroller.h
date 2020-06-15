#ifndef MANAGERLOGINCONTROLLER_H
#define MANAGERLOGINCONTROLLER_H

#include <QString>
#include <tuple>

#include "dbaccess.h"
#include "./listener.h"

class ManagerLoginController
{
public:
    ManagerLoginController() = delete;
    ManagerLoginController(const QString &Account, const QString &Password)
        : _account(Account), _password(Password){}
    std::tuple<bool, QString> ManagerLogin();
private:
    QString _account;//输入账号
    QString _password;//输入密码
    bool CheckArgs();//格式检查
    DBAccess db{};
};

#endif // MANAGERLOGINCONTROLLER_H
