#include "windcontroller.h"

WindController::WindController(QObject *parent, const bool open, const QString &RoomID)
    : QObject(parent), _open(open), _RoomID(RoomID)
{
    connect(this, SIGNAL(AddTextWind(QString)), parent, SLOT(TextAppend(QString)));
}

bool WindController::Send()
{

    WindRequest windrequest(_RoomID, _open);
    auto [error, result] = windrequest.Send();
    if(error.hasError()){
        qDebug() << "windcontroller error:";
        qDebug() << error.err_str;
        emit AddTextWind(error.err_str);
        emit AddTextWind("重试请求送风...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
        auto [error, result] = windrequest.Send();
        if(error.hasError()){
            emit AddTextWind("重试失败...");
        }
    }
    return result;
}
