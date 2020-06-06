#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

#include <optional>
#include <random>
#include <map>

enum class WorkingMode
{
    COLD = 0,
    HOT,
};

enum class SpeedLevel
{
    LOW = 0,
    MID,
    HIGH,
};

int getRandomInt(int low_bound, int up_bound);

class Config
{
public:
    static constexpr const char *kMasterHostAddr = "localhost";
    static constexpr quint16 kMasterListenPort = 12345;
    static constexpr int kRetryAttempt = 3;

    static quint16 getSlaveListenerPortValue();
    static void setSlaveListenerPort(const quint16 port);
    static bool hasSlaveListenerPort();

private:
    static std::optional<quint16> slave_listener_port;

};




#endif // COMMON_H