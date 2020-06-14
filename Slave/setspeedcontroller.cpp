#include "setspeedcontroller.h"

SetSpeedController::SetSpeedController(QObject *parent, const QString &RoomID, const SpeedLevel level)
    : QObject(parent), _RoomID(RoomID), _level(level)
{
    connect(this, SIGNAL(AddTextSpeed(QString)), parent, SLOT(TextAppend(QString)));
}

bool SetSpeedController::Set()
{
    SetSpeedRequest setspeedrequest(_RoomID, _level);
    auto [error, result] = setspeedrequest.Send();
    if(error.hasError()){
        qDebug() << "setspeedcontroller error:";
        qDebug() << error.err_str;
        emit AddTextSpeed(error.err_str);
        emit AddTextSpeed("重试设定风速...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
        auto [error, result] = setspeedrequest.Send();
        if(error.hasError()){
            emit AddTextSpeed("重试失败...");
        }
    }
    return result;
}
