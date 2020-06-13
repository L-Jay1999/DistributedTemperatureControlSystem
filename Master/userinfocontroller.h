#ifndef USERINFOCONTROLLER_H
#define USERINFOCONTROLLER_H

#include <tuple>
#include <QString>
#include <QDateTime>

#include "../CommonLib/dbaccess.h"

class UserInfoController
{
public:
    UserInfoController();
    std::tuple<bool,QString> AddUser(const QString &, const QString &);
    std::tuple<bool,QString> DeleteUser(const QString &RoomID, const QString &UserID);
    QString GetUser();
private:
    DBAccess dba{};
};

#endif // USERINFOCONTROLLER_H
