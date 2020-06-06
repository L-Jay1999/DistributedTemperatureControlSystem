#include "common.h"

#include <optional>

std::optional<quint16> Config::slave_listener_port = std::nullopt;

quint16 Config::getSlaveListenerPortValue() { return 0; }
void Config::setSlaveListenerPort() {  }
bool Config::hasSlaveListenerPort() { return true; }

