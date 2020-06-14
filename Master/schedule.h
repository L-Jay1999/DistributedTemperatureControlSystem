#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>
#include <vector>
#include <algorithm>
#include "../CommonLib/common.h"

class Schedule : public QObject
{
    Q_OBJECT
private:
    Config::RoomConfig defConf;//房间默认参数
    const int MAX_SERVICE = 3;//最大同时服务数量
    std::vector<QString> waiting_slave;//等待服务队列
    std::vector<QString> working_slave;//服务区
public:
    explicit Schedule(QObject *parent = nullptr);
    // 各操作的回复由上级controller完成
    void addRoom(const QString& RoomID);//将请求服务的从机加入等待队列
    void delRoom(const QString& RoomID);//将完成服务或已关闭的从机移出
    void checkIdle();//检查是否有空闲的服务区，若有则将等待队列头部的从机移入服务区
    //void SetSpeed(const QString& RoomID, const SpeedLevel& Level);//设置从控机风速
    //void SetTemperature(const QString& RoomID, const double& Degree);//设置从控机工作温度
signals:
    void work_signal(QString);//用于通知从控机开始工作
public slots:
};

#endif // SCHEDULE_H
