#ifndef MANAGERLOGINCONTROLLER_H
#define MANAGERLOGINCONTROLLER_H

#include <QString>
#include <tuple>

#include "dbaccess.h"
#include "listener.h"

class ManagerLoginController
{
public:
    ManagerLoginController() = delete;
    ManagerLoginController(const QString &Account, const QString &Password)
        : _Account(Account), _Password(Password){}
    std::tuple<bool, QString> ManagerLogin();
private:
    QString _Account;//输入账号
    QString _Password;//输入密码
    bool CheckArgs();//格式检查
    DBAccess db{};
};

#endif // MANAGERLOGINCONTROLLER_H
