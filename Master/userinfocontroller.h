#ifndef USERINFOCONTROLLER_H
#define USERINFOCONTROLLER_H

#include <tuple>
#include <QString>
#include <QDateTime>
class UserInfoController
{
public:
    UserInfoController();
    std::tuple<bool,QString> AddUser(const QString &, const QString &);
    std::tuple<bool,QString> DeleteUser(const QString &RoomID, const QString &UserID);
    QString GetUser();
private:
};

#endif // USERINFOCONTROLLER_H
