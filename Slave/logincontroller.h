#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include <QString>

class LoginController
{
public:
    LoginController();
    bool CheckArgs(QString UserID, QString RoomID);

private:
    class LoginRequest
    {
        //Config _config;
        //int _login_res;
        int SendRequest();
        int getLoginRes();
        int getConfig();
    }
};

#endif // LOGINCONTROLLER_H
