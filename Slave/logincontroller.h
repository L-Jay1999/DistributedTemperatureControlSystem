#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QString>
#include <tuple>

#include "requests.h"

class LoginController
{
public:
    LoginController() = delete;
    LoginController(const QString &UserID, const QString &RoomID, const quint16 &port)
        : _UserID(UserID), _RoomID(RoomID), _port(port)
    {}
    std::tuple<ErrorPack, bool, WorkingMode, double> Login();

private:
    QString _UserID;
    QString _RoomID;
    quint16 _port;
    bool CheckArgs();
};

#endif // LOGINCONTROLLER_H
