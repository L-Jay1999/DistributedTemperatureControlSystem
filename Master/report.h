#ifndef REPORT_H
#define REPORT_H
#include <vector>
#include <QString>
#include <QDateTime>
#include "global.h"
#include <map>
#include <utility>

class Report
{
public:
    Report();
    void writeDetail(const StatPayload &detail);//记录一个请求的详单，保存到数据库
    std::pair<bool,std::vector<StatPayload>> getDetails(const QDateTime &begin,const QDateTime &end,const QString &roomID);//向数据库查询begin-end时间段内指定从控机的详单
    bool getTodayReport();//从数据库获取所有从控机日报表，并保存在本地
    std::vector<StatPayload> getRoomReport(const QString &roomID);//从本地获取指定房间的日报表
private:
    QDateTime today = QDate::currentDate();//当天日期
    std::map<QString,std::vector<StatPayload>> _details{};//从控机日报表
    DBAccess &db = getDB();
};

#endif // REPORT_H
