#include "logincontroller.h"

std::tuple<bool, QString, WorkingMode, double> LoginController::Login()
{
    if(CheckArgs()){
        LoginRequest *loginrequest = new LoginRequest(_UserID, _RoomID, _port);
        std::tuple<bool, WorkingMode, double>result = loginrequest->Send();
        if(std::get<0>(result)){
            return {std::get<0>(result), "", std::get<1>(result), std::get<2>(result)};
        }
        else{
            return {false, "登陆失败", WorkingMode(), double()};
        }
    }
    else{
        return {false, "输入信息错误", WorkingMode(), double()};
        }
}

bool LoginController::CheckArgs()
{
    return true;
}
