#include "schedule.h"

Schedule::Schedule(QObject *parent) : QObject(parent)
{
    asc = new AirSupplyController(this, this);
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
        working_slave.erase(it);
        useandcost[*it]->UseandCostfromStart();
        delete useandcost[*it];
        checkIdle();//此时服务区有空闲，需要进行调度
        return;
    }
}

void Schedule::checkIdle()
{
    //若有服务可提供，且有从机处于等待队列中
    while(working_slave.size() < MAX_SERVICE && !waiting_slave.empty())
    {
        //将一台从机从等待队列移入服务区
        QString RoomID = waiting_slave.front();
        sic->Send(true,RoomID);
        working_slave.push_back(RoomID);
        waiting_slave.erase(waiting_slave.begin());
        UseAndCost *temp = new UseAndCost(this);
        if(useandcost[RoomID])
            delete useandcost[RoomID];
        useandcost[RoomID] = temp;
        temp->Start(RoomID);
    }
}
