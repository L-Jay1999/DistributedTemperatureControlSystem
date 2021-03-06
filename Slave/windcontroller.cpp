#include "windcontroller.h"

WindController::WindController(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(AddTextWind(QString)), parent, SLOT(TextAppend(QString)));
    connect(this, SIGNAL(ShutDown()), parent, SLOT(ForceShutDown()));
}

bool WindController::Send(const QString &RoomID, const bool open)
{

    WindRequest windrequest(RoomID, open);
    auto [error, result] = windrequest.Send();
    if(error.hasError()){
        qDebug() << "windcontroller error:";
        qDebug() << error.err_str;
        emit AddTextWind(error.err_str);
        emit AddTextWind("重试请求送风...");
        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(3000ms);
        auto [error, result] = windrequest.Send();
        if(error.hasError()){
            emit AddTextWind(error.err_str);
            emit AddTextWind("送风请求发送失败...");
            emit ShutDown();
        }
    }
    return result;
}
