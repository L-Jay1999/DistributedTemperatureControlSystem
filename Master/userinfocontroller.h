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
    std::pair<bool,QString> AddUser(const QString &, const QString &);
    std::pair<bool,QString> DeleteUser(const QString &RoomID, const QString &UserID);
    std::pair<bool, std::vector<std::pair<QString, QString>>> GetUser(); // <room_id, user_id>
private:
    // DBAccess dba{};
};

#endif // USERINFOCONTROLLER_H
