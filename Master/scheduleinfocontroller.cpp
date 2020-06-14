#include "scheduleinfocontroller.h"

ScheduleInfoController::ScheduleInfoController(QObject *parent) : QObject(parent)
{

}

bool ScheduleInfoController::Send(bool is_in_queue)
{
    ScheduleInfoRequest scheduleinforequest(is_in_queue);
    auto [error, res] = scheduleinforequest.Send();
    if(error.hasError()){
        qDebug() << "ScheduleInfoController error";
        qDebug() << error.err_str;
    }
    return res;
}
