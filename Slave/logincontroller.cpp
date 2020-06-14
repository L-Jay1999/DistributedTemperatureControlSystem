#include "logincontroller.h"

std::tuple<ErrorPack, bool, WorkingMode, double> LoginController::Login()
{
    LoginRequest loginrequest(_UserID, _RoomID, _port);
    std::tuple<ErrorPack, bool, WorkingMode, double>result = loginrequest.Send();
    return result;
}

bool LoginController::CheckArgs()
{
    return true;
}
