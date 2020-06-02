#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

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
static constexpr quint16 kMasterListenerPort = 12345;
static constexpr int kRetryAttempt = 3;

#endif // COMMON_H
