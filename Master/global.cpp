#include "global.h"

static Rooms rooms{};
Rooms &getRooms()
{
    return rooms;
}

static DBAccess db;
DBAccess &getDB()
{
    return db;
}
