#ifndef GLOBAL_H
#define GLOBAL_H

#include "../CommonLib/common.h"
#include "../CommonLib/dbaccess.h"

#include <map>
#include <set>
#include <vector>
#include <QDebug>
#include <mutex>

WorkingMode getCurrentWorkingMode();

void setCurrentWorkingMode(WorkingMode mode);

double getDefaultWorkingTemperature();

void setDefaultWorkingTemperature(double degree);

class Rooms;
Rooms &getRooms();

// 保存一个房间的设置信息
class RoomConfig
{
private:
    WorkingMode _mode{getCurrentWorkingMode()};//工作模式
    SpeedLevel _level{};//风速
    double _working_degree{getDefaultWorkingTemperature()};//工作温度
    double _current_degree{27.0};//当前温度
public:
    RoomConfig() {};
    RoomConfig(WorkingMode mode,SpeedLevel level,double wd,double cd)
        :   _mode(mode),_level(level),_working_degree(wd),_current_degree(cd)   {}
    RoomConfig(const RoomConfig& conf)
    {
        _mode = conf.getMode();
        _level = conf.getLevel();
        _working_degree = conf.getTemperature();
        _current_degree = conf.getCurTemperature();
    }
    void setMode(WorkingMode mode) {_mode = mode;}
    void setLevel(SpeedLevel level) {_level = level;}
    void setTemperature(double working_degree) {_working_degree = working_degree;}
    void setCurTemperature(double current_degree) {_current_degree = current_degree;}
    WorkingMode getMode() const {return _mode;}
    SpeedLevel getLevel() const {return _level;}
    double getTemperature() const {return _working_degree;}
    double getCurTemperature() const {return _current_degree;}
};

struct Room
{
    RoomConfig config{};
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

#endif // GLOBAL_H
