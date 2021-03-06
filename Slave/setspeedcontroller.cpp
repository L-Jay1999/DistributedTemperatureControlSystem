#include "setspeedcontroller.h"

SetSpeedController::SetSpeedController(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(AddTextSpeed(QString)), parent, SLOT(TextAppend(QString)));
    connect(this, SIGNAL(ShutDown()), parent, SLOT(ForceShutDown()));
}

bool SetSpeedController::Set(const QString &RoomID, const SpeedLevel level)
{
    SetSpeedRequest setspeedrequest(RoomID, level);
    auto [error, result] = setspeedrequest.Send();
    if(error.hasError()){
        qDebug() << "setspeedcontroller error:";
        qDebug() << error.err_str;
        emit AddTextSpeed(error.err_str);
        emit AddTextSpeed("重试设定风速...");
        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(3000ms);
        auto [error, result] = setspeedrequest.Send();
        if(error.hasError()){
            emit AddTextSpeed(error.err_str);
            emit AddTextSpeed("设置风速失败...");
            emit ShutDown();
        }
    }
    return result;
}
