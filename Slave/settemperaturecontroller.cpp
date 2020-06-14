#include "settemperaturecontroller.h"

SetTemperatureController::SetTemperatureController(QObject *parent, const QString &RoomID, const double degree)
    :  QObject(parent), _RoomID(RoomID), _degree(degree)
{
    connect(this, SIGNAL(AddTextTemp(QString)), parent, SLOT(TextAppend(QString)));
}

bool SetTemperatureController::Set()
{
    SetTemperatureRequest settemperaturerequest(_RoomID, _degree);
    auto [error, result] = settemperaturerequest.Send();
    if(error.hasError()){
        qDebug() << "settemperaturecontroller error:";
        qDebug() << error.err_str;
        emit AddTextTemp(error.err_str);
        emit AddTextTemp("重试设定温度...");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
        auto [error, result] = settemperaturerequest.Send();
        if(error.hasError()){
            emit AddTextTemp("重试失败...");
        }
    }
    return result;
}
