#include "user.h"

#include <shared_mutex>

static std::shared_mutex usage_rw_mtx;
static std::shared_mutex cost_rw_mtx;


QString User::getRoomID() const
{
    return _RoomID;
}

QString User::getUserID() const
{
    return _UserID;
}

double User::getUsage() const
{
    std::shared_lock lock(usage_rw_mtx);
    return _usage;
}

double User::getCost() const
{
    std::shared_lock lock(cost_rw_mtx);
    return _cost;
}

void User::setUsage(double usage)
{
    std::unique_lock lock(usage_rw_mtx);
    _usage = usage;
}

void User::setCost(double cost)
{
    std::unique_lock lock(cost_rw_mtx);
    _cost = cost;
}
