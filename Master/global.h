#ifndef GLOBAL_H
#define GLOBAL_H

#include "../CommonLib/common.h"
#include "../CommonLib/dbaccess.h"

#include <map>
#include <set>
#include <vector>
#include <QDebug>
#include <mutex>


struct Room
{
    Config::RoomConfig config{};
    //bool is_open{false};
    bool has_wind{false};
    QString room_id{};
    QString id{};
};

class Rooms
{
public:
    Rooms() {};
    void addRoom(const QString &room_id)
    {
        std::lock_guard lock(l1_mtx);
        qDebug() << "addRoom" << room_id;
        if (!hasRoom(room_id))
        {
            _connected_rooms.insert(room_id);
            _rooms[room_id] = {{}, {}, room_id, {}};
        }
    }

    Room &getRoom(const QString &room_id)
    {
        std::lock_guard lock(l1_mtx);
        return _rooms.at(room_id);
    }

    bool hasRoom(const QString &room_id)
    {
        std::lock_guard lock(l2_mtx);
        return _connected_rooms.count(room_id);
    }

    std::vector<QString> getRoomIDs()
    {
        std::lock_guard lock(l1_mtx);
        std::vector<QString> res;
        for (const auto room : _connected_rooms)
            res.push_back(room);
        return res;
    }

    void delRoomIfExists(const QString &room_id)
    {
        std::lock_guard lock(l1_mtx);
        qDebug() << "DelRoom" << room_id;
        if (hasRoom(room_id))
        {
            _connected_rooms.erase(room_id);
            _rooms.erase(room_id);
        }

    }

    void SetSpeed(const QString& RoomID, const SpeedLevel& Level)//设置从控机风速
    {
        std::lock_guard lock(l1_mtx);
        if (hasRoom(RoomID))
            _rooms[RoomID].config.setLevel(Level);
    }

    void SetTemperature(const QString& RoomID, const double& Degree)//设置从控机工作温度
    {
        std::lock_guard lock(l1_mtx);
        if (hasRoom(RoomID))
            _rooms[RoomID].config.setTemperature(Degree);
    }

    void SetID(const QString & RoomID, const QString &ID)
    {
        std::lock_guard lock(l1_mtx);
        if(hasRoom(RoomID))
        {
            _rooms[RoomID].id = ID;
//            qDebug() << "rooms " << RoomID << " sets " << ID;
        }
    }

private:
    std::mutex l1_mtx;
    std::mutex l2_mtx;
    std::map<QString, Room> _rooms;
    std::set<QString> _connected_rooms;
};

WorkingMode getCurrentWorkingMode();

void setCurrentWorkingMode(WorkingMode mode);

double getDefaultWorkingTemperature();

void setDefaultWorkingTemperature(double degree);


Rooms &getRooms();

#endif // GLOBAL_H
