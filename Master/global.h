#ifndef GLOBAL_H
#define GLOBAL_H

#include "../CommonLib/common.h"
#include "../CommonLib/dbaccess.h"
#include <map>
#include <set>
#include <vector>

struct Room
{
    Config::RoomConfig config{};
    bool is_open{false};
    bool has_wind{false};
    QString room_id{};
};

class Rooms
{
public:
    Rooms() {};
    void addRoom(const QString &room_id)
    {
        if (!_connected_rooms.count(room_id))
        {
            _connected_rooms.insert(room_id);
            _rooms[room_id] = Room{{}, {}, {}, room_id};
        }
    }

    const Room &getRoom(const QString &room_id) const
    {
        return _rooms.at(room_id);
    }

    Room &getRoom(const QString &room_id)
    {
        return _rooms.at(room_id);
    }

    std::vector<QString> getRoomIDs()
    {
        std::vector<QString> res;
        for (const auto room : _connected_rooms)
            res.push_back(room);
        return res;
    }

    void delRoomIfExists(const QString &room_id)
    {
        if (auto iter = _connected_rooms.find(room_id); iter != _connected_rooms.end())
        {
            _connected_rooms.erase(iter);
            _rooms.erase(_rooms.find(room_id));
        }
    }

    void SetSpeed(const QString& RoomID, const SpeedLevel& Level)//设置从控机风速
    {
        auto iter = _rooms.find(RoomID);
        if(iter != _rooms.end())
        {
            iter->secend.config.SetLevel(Level);
        }
    }

    void SetTemperature(const QString& RoomID, const double& Degree)//设置从控机工作温度
    {
        auto iter = _rooms.find(RoomID);
        if(iter != _rooms.end())
        {
            iter->secend.config.SetTemperature(Degree);
        }
    }

private:
    std::map<QString, Room> _rooms;
    std::set<QString> _connected_rooms;
};

Rooms &getRooms();

#endif // GLOBAL_H
