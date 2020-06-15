#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include "common.h"
#include "scheduleinfocontroller.h"
#include "airsupplycontroller.h"
#include "useandcost.h"

class AirSupplyController;
class Schedule : public QObject
{
    Q_OBJECT
private:
    bool _is_working;//是否工作
    const int MAX_SERVICE = 3;//最大同时服务数量
    std::deque<QString> waiting_slave;//等待服务队列
    std::deque<QString> working_slave;//服务区
    AirSupplyController *asc;   //送风请求接收控制器
    ScheduleInfoController *sic;//送风请求回复控制器
    std::map<QString, UseAndCost*> useandcost;
public:
    explicit Schedule(QObject *parent = nullptr);
    // 各操作的回复由上级controller完成
    void addRoom(const QString& RoomID);//将请求服务的从机加入等待队列
    void delRoom(const QString& RoomID);//将完成服务或已关闭的从机移出
    void checkIdle();//检查是否有空闲的服务区，若有则将等待队列头部的从机移入服务区

};

#endif // SCHEDULE_H
