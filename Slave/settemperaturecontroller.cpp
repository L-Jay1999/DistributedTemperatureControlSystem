#include "settemperaturecontroller.h"

SetTemperatureController::SetTemperatureController(QObject *parent)
    :  QObject(parent)
{
    connect(this, SIGNAL(AddTextTemp(QString)), parent, SLOT(TextAppend(QString)));
    connect(this, SIGNAL(ShutDown()), parent, SLOT(ForceShutDown()));
}

bool SetTemperatureController::Set(const QString &RoomID, const double degree)
{
    SetTemperatureRequest settemperaturerequest(RoomID, degree);
    auto [error, result] = settemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "settemperaturecontroller error:";
        qDebug() << error.err_str;
        emit AddTextTemp(error.err_str);
        emit AddTextTemp("重试设定温度...");
        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(3000ms);
        auto [error, result] = settemperaturerequest.Send();
        if(error.hasError()){
            emit AddTextTemp(error.err_str);
            emit AddTextTemp("设定温度失败...");
            emit ShutDown();
        }
    }
    return result;
}
