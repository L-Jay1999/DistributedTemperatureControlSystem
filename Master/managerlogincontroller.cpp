
#include "managerlogincontroller.h"

std::tuple<bool, QString> ManagerLoginController::ManagerLogin()
{
    if(CheckArgs()){
        //bool result = db.hasManager(_Account,_Password);
        bool result = true;
        if(result){
            return {true, "Succeed"};
        }
        else{
            return {false, "Incorrect password or account doesn't exist."};
        }
    }
    else{
        return {false, "Input format error."};
    }
}

bool ManagerLoginController::CheckArgs()
{
    return true;
}
