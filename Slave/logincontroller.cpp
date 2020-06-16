#include "logincontroller.h"

std::tuple<ErrorPack, bool, WorkingMode, double> LoginController::Login()
{
    if (!CheckArgs())
    {
        ErrorPack err;
        err.setParsingError({});
        err.err_str = "身份证格式错误或者房间号为空";
        return {err, false, {}, {}};
    }
    LoginRequest loginrequest(_UserID, _RoomID, _port);
    std::tuple<ErrorPack, bool, WorkingMode, double>result = loginrequest.Send();
    return result;
}

bool LoginController::CheckArgs()
{
#ifdef ENABLE_ARG_CHECK
    QRegExp re("[0-9]{17}[0-9xX]");
    return re.exactMatch(_UserID) && _RoomID.length();
#else
    return true;
#endif
}
