#include "userinfocontroller.h"
#include "standbywidget.h"

UserInfoController::UserInfoController()
{
}

std::tuple<bool, QString> UserInfoController::AddUser(const QString &RoomID, const QString &UserID)
{
    if (dba.isConnected() == true) //判断是否连接至数据库
    {
        if (dba.hasUser(RoomID, UserID) == false) //判断是否已存在该用户
        {
            bool res = dba.addUser(RoomID, UserID); //进行插入操作
            if (res == true)
            {
                return {true, QStringLiteral("添加成功")};
            }
            else
            {
                return {false, QStringLiteral("添加失败：数据库插入失败")};
            }
        }
        else
        {
            return {false, QStringLiteral("添加失败：已存在的用户")};
        }
    }
    else
    {
        return {false, QStringLiteral("添加失败：数据库无连接")};
    }
}
std::tuple<bool, QString> UserInfoController::DeleteUser(const QString &RoomID, const QString &UserID)
{
    if (dba.isConnected() == true) //判断是否连接至数据库
    {
        if (dba.hasUser(RoomID, UserID) == true) //判断是否已存在该用户
        {
            bool res = dba.delUser(RoomID, UserID); //进行删除操作
            if (res == true)
            {
                return {true, QStringLiteral("删除成功")};
            }
            else
            {
                return {false, QStringLiteral("删除失败：数据库删除失败")};
            }
        }
        else
        {
            return {false, QStringLiteral("删除失败：不存在该用户")};
        }
    }
    else
    {
        return {false, QStringLiteral("删除失败：数据库无连接")};
    }
}

QString UserInfoController::GetUser()
{
    auto UserInfo = dba.getUsers();
    if (UserInfo.first == true)
    {
        QString result;
        result.clear();
        for (auto it = UserInfo.second.begin(); it != UserInfo.second.end(); it++)
        {
            result = result + std::get<0>(*it) + "\t" + std::get<1>(*it) + "\t" + QString::number(std::get<2>(*it)) + "\t" + QString::number(std::get<3>(*it)) + "\n";
        }
        return result;
    }
    else
    {
        return QStringLiteral("用户信息获取失败");
    }
}
