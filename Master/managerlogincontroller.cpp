
#include "managerlogincontroller.h"

std::tuple<bool, QString> ManagerLoginController::ManagerLogin()
{
    if(CheckArgs()){
        //bool result = db.hasManager(_Account,_Password);
        bool result = true;
        if(result){
            return (std::tuple<bool,QString>){true, "Succeed"};
        }
        else{
            return (std::tuple<bool,QString>){false, "Incorrect password or account doesn't exist."};
        }
    }
    else{
        return (std::tuple<bool,QString>){false, "Input format error."};
    }
}

bool ManagerLoginController::CheckArgs()
{
    return true;
}
