#include "global.h"

static Rooms rooms{};
Rooms &getRooms()
{
    return rooms;
}

static Schedule schedule;
Schedule &getSchedule()
{
    return schedule;
}
