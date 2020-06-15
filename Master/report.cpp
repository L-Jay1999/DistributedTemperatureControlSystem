#include "report.h"

#include <utility>

Report::Report()
{
}

std::pair<bool,std::vector<StatPayload>> Report::getDetails(const QDateTime &begin,const QDateTime &end)
{
    DBAccess db;
    return db.getRoomRequestStats(begin,end);//获取当日报表
}

bool Report::getDateReport(const QDate &date)
{
    DBAccess db;
    QDateTime begin, end;
    begin.setDate(date);
    end.setDate(date.addDays(1));
    std::pair<bool, std::vector<StatPayload>> res_detail = db.getRoomRequestStats(begin,end);//获取当日报表
    std::pair<bool, std::vector<std::tuple<QString, bool, QDateTime>>> res_power = db.getRoomPowerStats(begin,end);//获取开关机事件
    if(res_detail.first == false || res_power.first == false)
        return false;
    _details.clear();
    for(auto it = res_detail.second.begin(); it != res_detail.second.end(); it++)//将报表按照房间号拆分
    {
        _details[it->room_id].push_back(*it);
    }
    _power_supply.clear();
    for(auto it = res_power.second.begin(); it != res_power.second.end(); it++)//统计各房间开关机次数
    {
        QString roomid = std::get<0>(*it);
        auto it2 = _power_supply.find(roomid);
        if(it2 != _power_supply.end())
        {
            _power_supply[roomid] += 1;
        }else
        {
            _power_supply[roomid] = 1;
        }
    }
}

std::vector<StatPayload> Report::getRoomReport(const QString &roomID)
{
    auto it = _details.find(roomID);
    if(it != _details.end())
        return it->second;
    return {};
}

int Report::getPowerSupply(const QString &roomID)
{
    auto it = _details.find(roomID);
    if(it != _details.end())
        return _power_supply[roomID];
    return 0;
}

double Report::getCost(const QString &roomID)
{
    double cost = 0.0;
    for(auto it = _details[roomID].begin(); it != _details[roomID].end(); it++)
        cost += it->cost;
    return cost;
}
