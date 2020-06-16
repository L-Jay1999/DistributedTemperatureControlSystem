#include "userinfocontroller.h"
#include "standbywidget.h"

UserInfoController::UserInfoController()
{
}

std::pair<bool, QString> UserInfoController::AddUser(const QString &RoomID, const QString &UserID)
{
    DBAccess db;
    if (db.isConnected() == true) //判断是否连接至数据库
    {
        if (db.hasUser(RoomID, UserID) == false) //判断是否已存在该用户
        {
            bool res = db.addUser(RoomID, UserID); //进行插入操作
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
std::pair<bool, QString> UserInfoController::DeleteUser(const QString &RoomID, const QString &UserID)
{
    DBAccess db;
    if (db.isConnected() == true) //判断是否连接至数据库
    {
        if (db.hasUser(RoomID, UserID) == true) //判断是否已存在该用户
        {
            bool res = db.delUser(RoomID, UserID); //进行删除操作
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

std::pair<bool, std::vector<std::pair<QString, QString>>> UserInfoController::GetUser()
{
    DBAccess db;
    auto [is_suc, users] = db.getUsers();
    std::vector<std::pair<QString, QString>> res;
    if (is_suc)
        for (const auto user : users)
            res.push_back({std::get<0>(user), std::get<1>(user)});
    return {is_suc, res};
}
