#include "useandcostcontrollermaster.h"

UseAndCostControllerMaster::UseAndCostControllerMaster(QObject *parent)
    : QObject(parent) , _rooms(getRooms())
{
    
}

bool UseAndCostControllerMaster::Send(const double use, const double cost, const QString &RoomID)
{
    using namespace std::chrono_literals;
    UseAndCostRequest useandcostrequest(use, cost, RoomID);
    auto [error, res] = useandcostrequest.Send();
    if(error.hasError()){
        qDebug() << "UseandCostControllerMaster error, retransmission";
        qDebug() << error.err_str;
        std::this_thread::sleep_for(1000ms);
        auto [re_error, re_res] = useandcostrequest.Send();
        if (error.hasError())
        {
            _rooms.delRoomIfExists(RoomID);
        }

    }
    return res;
}
