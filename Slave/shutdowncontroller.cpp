#include "shutdowncontroller.h"

ShutDownController::ShutDownController(QObject *parent, const QString &RoomID)
    : QObject(parent), _RoomID(RoomID)
{
    connect(this, SIGNAL(AddTextShutDown(QString)), parent, SLOT(TextAppend(QString)));
}

bool ShutDownController::ShutDown()
{
    ShutDownRequest shutdownrequest(_RoomID);
    auto [error, result] = shutdownrequest.Send();
    if(error.hasError()){
        qDebug() << "shutdowncontroller error:";
        qDebug() << error.err_str;
        emit AddTextShutDown(error.err_str);
        emit AddTextShutDown("重试关机...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
        auto [error, result] = shutdownrequest.Send();
        if(error.hasError()){
            emit AddTextShutDown("重试失败...");
        }
    }
    return result;
}
