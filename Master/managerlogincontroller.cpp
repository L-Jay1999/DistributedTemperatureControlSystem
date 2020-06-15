
#include "managerlogincontroller.h"

#include <QRegExp>

std::tuple<bool, QString> ManagerLoginController::ManagerLogin()
{
//    return {true, {}};

    if (CheckArgs())
    {
        bool result = db.hasManager(_account,_password);
        if (result)
        {
            return {true, QStringLiteral("登录成功")};
        }
        else
        {
            return {false, QStringLiteral("账户不存在或密码错误")};
        }
    }
    else
    {
        return {false, "账号和密码必须为3到12位的数字字母字符串"};
    }
}

bool ManagerLoginController::CheckArgs()
{
    QRegExp re("[a-zA-Z0-9]{3,12}");
    if (re.exactMatch(_account) && re.exactMatch(_password))
        return true;
    return false;
}
