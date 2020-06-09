#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include <QString>
#include <tuple>
#include "../CommonLib/requests.h"

class LoginController
{
public:
    LoginController() = delete;
    LoginController(const QString &UserID, const QString &RoomID, const quint16 &port)
        : _UserID(UserID), _RoomID(RoomID), _port(port)
    {}
    std::tuple<bool, QString, WorkingMode, double> Login();


private:
    QString _UserID;
    QString _RoomID;
    QString _port;
    bool CheckArgs();

};

#endif // LOGINCONTROLLER_H
