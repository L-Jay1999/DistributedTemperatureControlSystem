#include "common.h"

#include <optional>
#include <cassert>
#include <shared_mutex>
#include <mutex>


std::optional<quint16> Config::slave_listener_port = std::nullopt;
static std::shared_mutex rw_mutex;

quint16 Config::getSlaveListenerPortValue()
{
    std::shared_lock lock(rw_mutex);
    assert(slave_listener_port.has_value());
    return slave_listener_port.value();
}

void Config::setSlaveListenerPort(const quint16 port)
{
    std::unique_lock lock(rw_mutex);
    slave_listener_port = port;
}

bool Config::hasSlaveListenerPort()
{
    std::shared_lock lock(rw_mutex);
    return slave_listener_port.has_value();
}




