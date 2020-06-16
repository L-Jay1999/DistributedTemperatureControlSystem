#include "shutdowncontroller.h"

ShutDownController::ShutDownController(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(AddTextShutDown(QString)), parent, SLOT(TextAppend(QString)));
    connect(this, SIGNAL(ShutDown()), parent, SLOT(ForceShutDown()));
}

bool ShutDownController::ShutDown(const QString &RoomID)
{
    ShutDownRequest shutdownrequest(RoomID);
    auto [error, result] = shutdownrequest.Send();
    if(error.hasError()){
        qDebug() << "shutdowncontroller error:";
        qDebug() << error.err_str;
        emit AddTextShutDown(error.err_str);
        emit AddTextShutDown("重试关机...");
        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(3000ms);
        auto [error, result] = shutdownrequest.Send();
        if(error.hasError()){
            emit AddTextShutDown(error.err_str);
            emit AddTextShutDown("发送关机请求失败...");
            emit ShutDown();
        }
    }
    return result;
}
