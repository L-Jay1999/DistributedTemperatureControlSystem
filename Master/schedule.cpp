#include "schedule.h"

//Schedule::Schedule(QObject *parent) : QObject(parent)
//{

//}

void Schedule::addRoom(const QString& RoomID,const Config::RoomConfig& conf)
{
    class Service s(RoomID,conf);
    waiting_slave.push_back(s);
}

void Schedule::delRoom(const QString &RoomID)
{
    for(auto it = waiting_slave.begin();it != waiting_slave.end();it++)
    {
        if((*it).getRoomID() == RoomID)
        {
            waiting_slave.erase(it);
            return;
        }
    }
    for(auto it = working_slave.begin();it != working_slave.end();it++)
    {
        if((*it).getRoomID() == RoomID)
        {
            working_slave.erase(it);
            return;
        }
    }
}

void Schedule::checkIdle()
{
    //若有服务可提供，且有从机处于等待队列中
    while(working_slave.size()<MAX_SERVICE && !waiting_slave.empty())
    {
        //将一台从机从等待队列移入服务区
        emit work_signal(waiting_slave.front());
        working_slave.push_back(waiting_slave.front());
        waiting_slave.erase(waiting_slave.begin());
    }
}

void Schedule::SetSpeed(const QString &RoomID, const SpeedLevel &Level)
{

}
