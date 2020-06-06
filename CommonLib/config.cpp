#include "common.h"

#include <optional>
#include <cassert>
#include <shared_mutex>
#include <mutex>

#include <QString>

namespace Config
{
    static std::optional<quint16> slave_listener_port = std::nullopt;
    static std::map<QString, std::pair<QString, quint16>> roomid_to_address{};
    // 确保线程安全
    static std::shared_mutex slave_port_rw_mutex;
    static std::shared_mutex roomid_to_addr_rw_mutex;

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
} // namespace Config
