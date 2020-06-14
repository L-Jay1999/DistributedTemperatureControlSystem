#include "schedule.h"

Schedule::Schedule(QObject *parent) : QObject(parent)
{

}

Service::Service(const Service& ser)
{
    _roomID = ser.getRoomID();
    _config = ser.getConfig();
}

void Schedule::addRoom(const QString& RoomID)
{
    waiting_slave.push_back(RoomID);
}

void Schedule::delRoom(const QString &RoomID)
{
    auto it = std::find(waiting_slave.begin(),waiting_slave.end(),RoomID);
    if(it != waiting_slave.end())
    {
        waiting_slave.erase(it);
        return;
    }
    it = std::find(working_slave.begin(),working_slave.end(),RoomID);
    if(it != working_slave.end())
    {
        working_slave.erase(it);
        return;
    }
}

void Schedule::checkIdle()
{
    //若有服务可提供，且有从机处于等待队列中
    while(working_slave.size() < MAX_SERVICE && !waiting_slave.empty())
    {
        //将一台从机从等待队列移入服务区
        emit work_signal(waiting_slave.front());
        working_slave.push_back(waiting_slave.front());
        waiting_slave.erase(waiting_slave.begin());
    }
}
/*
void Schedule::SetSpeed(const QString &RoomID, const SpeedLevel &Level)
{
    Config::RoomConfig conf;
    auto it = find(waiting_slave,RoomID);
    if(it != waiting_slave.end())
    {
        conf = (*it).getConfig();
        conf.setLevel(Level);
        (*it).updateConfig(conf);
        return;
    }
    it = find(working_slave,RoomID);
    if(it != working_slave.end())
    {
        conf = (*it).getConfig();
        conf.setLevel(Level);
        (*it).updateConfig(conf);
        return;
    }
}

void Schedule::SetTemperature(const QString &RoomID, const double &Degree)
{
    Config::RoomConfig conf;
    auto it = find(waiting_slave,RoomID);
    if(it != waiting_slave.end())
    {
        conf = (*it).getConfig();
        conf.setTemperature();
        (*it).updateConfig(conf);
        return;
    }
    it = find(working_slave,RoomID);
    if(it != working_slave.end())
    {
        conf = (*it).getConfig();
        conf.setTemperature();
        (*it).updateConfig(conf);
        return;
    }
}
*/
