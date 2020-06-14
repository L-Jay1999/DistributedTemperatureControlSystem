
#include "managerlogincontroller.h"

std::tuple<bool, QString> ManagerLoginController::ManagerLogin()
{
    return {true, {}};

    if (CheckArgs())
    {
        bool result = db.hasManager(_Account,_Password);
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
        return {false, "输入格式有误"};
    }
}

bool ManagerLoginController::CheckArgs()
{
    return true;
}
