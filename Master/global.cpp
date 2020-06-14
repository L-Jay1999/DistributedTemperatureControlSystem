#include "global.h"

static Rooms rooms{};
Rooms &getRooms()
{
    return rooms;
}
