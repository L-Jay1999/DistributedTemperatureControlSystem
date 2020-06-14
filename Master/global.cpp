#include "global.h"

static Rooms rooms{};
Rooms &getRooms()
{
    return rooms;
}

static WorkingMode mode;

WorkingMode getCurrentWorkingMode()
{
    return mode;
}

void setCurrentWorkingMode(const WorkingMode working_mode)
{
   mode = working_mode;
}
