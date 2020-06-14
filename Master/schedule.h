#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>
#include <vector>
#include "../CommonLib/common.h"
class Service
{
public:
    Service() = delete;
    Service(const QString& roomID,const Config::RoomConfig& config):_roomID(roomID),_config(config){}
    Service(const Service& ser);
    QString getRoomID(){return _roomID;}
    Config::RoomConfig getConfig(){return _config;}
    void updateConfig(Config::RoomConfig config){_config = config;}
private:
    QString _roomID;//房间号
    Config::RoomConfig _config;//房间参数
};

class Schedule : public QObject
{
    Q_OBJECT
private:
    Config::RoomConfig defConf;//房间默认参数
    const int MAX_SERVICE = 3;//最大同时服务数量
    std::vector<Service> waiting_slave;//等待服务队列
    std::vector<Service> working_slave;//服务区
public:
    explicit Schedule(QObject *parent = nullptr);
signals:
    void work_signal(Service);//用于通知从控机开始工作
public slots:
    // 各操作的回复由上级controller完成
    void addRoom(const QString& RoomID,const Config::RoomConfig& conf);//将请求服务的从机加入等待队列
    void delRoom(const QString& RoomID);//将完成服务或已关闭的从机移出
    void checkIdle();//检查是否有空闲的服务区，若有则将等待队列头部的从机移入服务区
    void SetSpeed(const QString& RoomID, const SpeedLevel& Level);//设置从控机风速
    void SetTemperature(const QString& RoomID, const double& Degree);//设置从控机工作温度
};

auto find(const std::vector<Service>& slave, const QString& RoomID)
{
    for(auto it = slave.begin();it != slave.end();it++)
    {
        if((*it).getRoomID == RoomID)
        {
            return it;
        }
    }
    return slave.end();
}

#endif // SCHEDULE_H