
#include "managerlogincontroller.h"

std::tuple<bool, QString> ManagerLoginController::ManagerLogin()
{
    if(CheckArgs()){
        ManagerLoginRequest *managerloginrequest = new ManagerLoginRequest(_Account, _Password, _port);//建立请求
        bool result = managerloginrequest->Send();//发送请求
        if(result){
            delete loginrequest;
            return {true, "认证成功"};
        }
        else{
            delete loginrequest;
            return {false, "密码错误或账号不存在"};
        }
    }
    else{
        return {false, "输入格式错误"};
    }
}

