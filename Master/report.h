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
    bool getDateReport(const QDate &date);//从数据库获取从控机日报表，并保存在本地
    std::pair<bool,std::vector<StatPayload>> getDetails(const QDateTime &begin,const QDateTime &end);//向数据库查询begin-end时间段内所有从控机的详单
    std::vector<StatPayload> getRoomReport(const QString &roomID);//从本地获取指定房间的日报表
    int getPowerSupply(const QString &roomID);//获取开关机次数
    double getCost(const QString &roomID);//获取当日总费用
private:
    std::map<QString,int> _power_supply;//开关机次数
    std::map<QString,std::vector<StatPayload>> _details{};//日报表
    DBAccess db;
};

#endif // REPORT_H
