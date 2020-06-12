#include "user.h"

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
    return _usage;
}

double User::getCost() const
{
    return _cost;
}
