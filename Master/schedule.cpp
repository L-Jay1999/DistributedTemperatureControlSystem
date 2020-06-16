﻿#include "schedule.h"

Schedule::Schedule(std::map<QString, std::shared_ptr<UseAndCost>> &u, QObject *parent) : QObject(parent), useandcost(u)
{
    asc = new AirSupplyController(*this, this);
    sic = new ScheduleInfoController(this);
}

void Schedule::addRoom(const QString& RoomID)
{
    waiting_slave.push_back(RoomID);
    checkIdle();
}

void Schedule::delRoom(const QString &RoomID)
{
    auto it = std::find(waiting_slave.begin(), waiting_slave.end(), RoomID);
    if(it != waiting_slave.end())
    {
        waiting_slave.erase(it);
        return;
    }
    it = std::find(working_slave.begin(),working_slave.end(),RoomID);
    if(it != working_slave.end())
    {
        sic->Send(false,*it);
        getRooms().getRoom(RoomID).has_wind = false;
        if(useandcost.count(*it)){
            //构造详单，发送给数据库
            struct StatPayload sp;
            useandcost[*it]->UseandCostfromStart(sp);
            DBAccess db;
            if(db.addRoomRequestStat(sp) == false)
            {
                qDebug() << "Schedule::delRoom::db.addRoomRequestStat Error";
            }
            useandcost.erase(*it);
        }
        working_slave.erase(it);
        checkIdle();//此时服务区有空闲，需要进行调度
    }
}

void Schedule::checkIdle()
{
    //若有服务可提供，且有从机处于等待队列中
    while(working_slave.size() < MAX_SERVICE && !waiting_slave.empty())
    {
        //将一台从机从等待队列移入服务区
        QString RoomID = waiting_slave.front();
        qDebug() << RoomID << "is taken out of waiting slave";
        sic->Send(true, RoomID);
        getRooms().getRoom(RoomID).has_wind = true;
        working_slave.push_back(RoomID);
        waiting_slave.pop_front();
        useandcost[RoomID] = std::make_shared<UseAndCost>(this);
        useandcost[RoomID]->Start(RoomID);
    }
}
