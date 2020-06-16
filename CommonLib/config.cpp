#include "common.h"

#include <optional>
#include <cassert>
#include <shared_mutex>
#include <mutex>

#include <QString>
#include <QObject>
#include <QDebug>


namespace Config
{
    static std::optional<quint16> slave_listener_port = std::nullopt;
    static std::map<QString, std::pair<QString, quint16>> roomid_to_address{};
    static std::optional<UserType> user_type = std::nullopt;
    static std::map<SlaveControllerType, QObject *> slave_ctrller_ptr{};
    static std::map<MasterControllerType, QObject *> master_ctrller_ptr{};
    static constexpr auto kMasterDBPath = "./master.db";
    static constexpr auto kSlaveDBPath = "./slave.db";
    static int timeout_msec = 1000;
    // 确保线程安全
    static std::shared_mutex slave_port_rw_mutex;
    static std::shared_mutex roomid_to_addr_rw_mutex;
    static std::shared_mutex user_type_rw_mutex;
    static std::shared_mutex slave_ctrller_ptr_rw_mutex;
    static std::shared_mutex timeout_ms_rw_mutex;
    static std::shared_mutex master_ctrller_ptr_rw_mutex;

    quint16 getSlaveListenerPortValue()
    {
        std::shared_lock lock(slave_port_rw_mutex);
        assert(slave_listener_port.has_value());
        return slave_listener_port.value();
    }

    void setSlaveListenerPort(const quint16 port)
    {
        std::unique_lock lock(slave_port_rw_mutex);
        slave_listener_port = port;
    }

    void clearSlaveListenerPort()
    {
        std::unique_lock lock(slave_port_rw_mutex);
        slave_listener_port.reset();
    }

    bool hasSlaveListenerPort()
    {
        std::shared_lock lock(slave_port_rw_mutex);
        return slave_listener_port.has_value();
    }

    void addAddress(const QString &room_id, const QString &host_addr, const quint16 port)
    {
        std::unique_lock lock(roomid_to_addr_rw_mutex);
        roomid_to_address.at(room_id) = {host_addr, port};
    }

    std::pair<bool, std::pair<QString, quint16>> getAddress(const QString &room_id)
    {
        std::shared_lock lock(roomid_to_addr_rw_mutex);
        if (auto iter = roomid_to_address.find(room_id); iter != roomid_to_address.end())
            return {true, (*iter).second};
        return {false, {}};
    }

    void setUserType(const UserType user_type)
    {
        std::unique_lock lock(user_type_rw_mutex);
        Config::user_type = user_type;
    }

    std::optional<UserType> getUserType()
    {
        std::shared_lock lock(user_type_rw_mutex);
        return user_type;
    }

    bool hasUserType()
    {
        std::shared_lock lock(user_type_rw_mutex);
        return user_type.has_value();
    }

    QString getDBPath()
    {
        QString path;
        if (getUserType().has_value())
            path = (getUserType().value() == UserType::MASTER) ? kMasterDBPath : kSlaveDBPath;
        return path;
    }

    void setSlaveControllerPointer(SlaveControllerType type, QObject *controller)
    {
        std::unique_lock lock(slave_ctrller_ptr_rw_mutex);
        qDebug() << "Config::setSlaveControllerPointer() set type: " << EnumToInt(type);
        slave_ctrller_ptr[type] = controller;
    }

    QObject *getSlaveControllerPointer(SlaveControllerType ctrller_type)
    {
        std::shared_lock lock(slave_ctrller_ptr_rw_mutex);
        if (auto i = slave_ctrller_ptr.find(ctrller_type);
                i != slave_ctrller_ptr.end())
            return (*i).second;
        // qDebug() << "Config::getSlaveControllerPointer() of type: " << EnumToInt(ctrller_type) << " not set.";
        return nullptr;
    }

    void setMasterControllerPointer(MasterControllerType type, QObject *controller)
    {
        std::unique_lock lock(master_ctrller_ptr_rw_mutex);
        // slave_ctrller_ptr.at(type) = controller;
        qDebug() << "Config::setMasterControllerPointer() set type: " << EnumToInt(type);
        master_ctrller_ptr[type] = controller;
    }

    QObject *getMasterControllerPointer(MasterControllerType ctrller_type)
    {
        std::shared_lock lock(master_ctrller_ptr_rw_mutex);
        if (auto i = master_ctrller_ptr.find(ctrller_type);
                i != master_ctrller_ptr.end())
            return (*i).second;
        // qDebug() << "Config::getMasterControllerPointer() of type: " << EnumToInt(ctrller_type) << " not set.";
        return nullptr;
    }

    void setTimeOutMsec(int timeout_ms)
    {
        std::unique_lock lock(timeout_ms_rw_mutex);
        timeout_msec = timeout_ms;
    }

    int getTimeOutMSec()
    {
        std::shared_lock lock(timeout_ms_rw_mutex);
        return timeout_msec;
    }

    static std::map<QString, quint16> room_to_port{};
    void addSlavePort(const QString &room_id, quint16 port)
    {
        room_to_port[room_id] = port;
        // qDebug() << "Config::addSlavePort(): room: " << room_id << ", port: " << port;
    }

    quint16 getSlavePort(const QString &room_id)
    {
        if (room_to_port.count(room_id))
            return room_to_port[room_id];
        return {};
    }

    void delSlavePort(const QString &room_id)
    {
        if (auto iter = room_to_port.find(room_id); iter != room_to_port.end())
            room_to_port.erase(iter);
    }
} // namespace Config
