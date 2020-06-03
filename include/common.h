#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

#include <optional>
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

static constexpr const char *kMasterHostAddr = "localhost";
static constexpr quint16 kMasterListenPort = 12345;
static constexpr int kRetryAttempt = 3;
static constexpr int kSlaveListenPort = 54321;

// 记录从控机监听端口
// extern std::map<QString, quint16> slaveListenerPortMap;


#endif // COMMON_H
