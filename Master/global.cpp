#include "global.h"

static Rooms rooms{};
Rooms &getRooms()
{
    return rooms;
}

static WorkingMode working_mode;
static std::map<WorkingMode, double> default_degree =
{
    {WorkingMode::HOT, 28.0},
    {WorkingMode::COLD, 25.0},
};

WorkingMode getCurrentWorkingMode()
{
    return working_mode;
}

void setCurrentWorkingMode(const WorkingMode mode)
{
   working_mode = mode;
}

double getDefaultWorkingTemperature()
{
    return default_degree.at(working_mode);
}

void setDefaultWorkingTemperature(double degree)
{
    default_degree.at(working_mode) = degree;
}
