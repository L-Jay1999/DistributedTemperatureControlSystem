#ifndef REPORT_H
#define REPORT_H
#include <vector>
#include <QString>
#include <QDateTime>
#include <map>
#include <utility>
#include "../CommonLib/dbaccess.h"
#include "../CommonLib/common.h"

class Report
{
public:
    Report();
    bool Report::writeDetail(const StatPayload &detail);//记录一个请求的详单，保存到数据库
    std::pair<bool,std::vector<StatPayload>> getDetails(const QDateTime &begin,const QDateTime &end,const QString &roomID);//向数据库查询begin-end时间段内指定从控机的详单
    bool getTodayReport(const QDate &date);//从数据库获取从控机日报表，并保存在本地
    std::vector<StatPayload> getRoomReport(const QString &roomID);//从本地获取指定房间的日报表
private:
    std::map<QString,int> _power_supply;//开关机次数
    std::map<QString,double> _total_cost;//当日所需总费用
    std::map<QString,std::vector<StatPayload>> _details{};//日报表
    DBAccess db;
};

#endif // REPORT_H
