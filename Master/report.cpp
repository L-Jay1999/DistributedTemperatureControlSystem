#include "report.h"

#include <utility>

Report::Report()
{
}

std::pair<bool,std::vector<StatPayload>> Report::getDetails(const QDateTime &begin,const QDateTime &end,const QString &roomID)
{
    std::pair<bool, std::vector<StatPayload>> response = db.getRoomRequestStats(begin,end);//获取当日报表
    if(response.first == false)return response;
    for(auto it = response.second.begin(); it != response.second.end();)
    {
        if(it->room_id != roomID)//去除不需要的详单
        {
            response.second.erase(it);
        }else
        {
            it++;
        }
    }
    return response;
}

bool Report::getTodayReport(const QDate &date)
{
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


}

bool Report::writeDetail(const StatPayload &detail)
{
    return db.addRoomRequestStat(detail);
}

std::vector<StatPayload> Report::getRoomReport(const QString &roomID)
{
    auto it = _details.find(roomID);
    if(it != _details.end())
        return it->second;
    return {};
}
