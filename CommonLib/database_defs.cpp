#include "database_defs.h"

const std::vector<DBHelper::ColPayload> LogContract::COL_INFO =
{
    {"time", DBHelper::ColTypes::INTEGER, false, true},
    {"level", DBHelper::ColTypes::INTEGER, false, true},
    {"content", DBHelper::ColTypes::TEXT, false, true},
};

const std::vector<DBHelper::ColPayload> MasterUserContract::COL_INFO =
{
    {"room", DBHelper::ColTypes::TEXT, true, true},
    {"id", DBHelper::ColTypes::TEXT, true, true},
    {"use", DBHelper::ColTypes::NUMERIC, false, true, true, "0"},
    {"cost", DBHelper::ColTypes::NUMERIC, false, true, true, "0"},
};

const std::vector<DBHelper::ColPayload> MasterAuthContract::COL_INFO =
{
    {"account", DBHelper::ColTypes::TEXT, true, true},
    {"password", DBHelper::ColTypes::TEXT, false, true},
};

const std::vector<DBHelper::ColPayload> MasterPowerStatContract::COL_INFO =
{
    {"room", DBHelper::ColTypes::TEXT, false, true},
    {"is_start_up", DBHelper::ColTypes::INTEGER, false, true},
    {"time", DBHelper::ColTypes::INTEGER, false, true},
};

const std::vector<DBHelper::ColPayload> MasterRequestStatContract::COL_INFO =
{
    {"room", DBHelper::ColTypes::TEXT, false, true},
    {"initial_temperature", DBHelper::ColTypes::NUMERIC, false, true},
    {"target_temperature", DBHelper::ColTypes::NUMERIC, false, true},
    {"start_time", DBHelper::ColTypes::INTEGER, false, true},
    {"end_time", DBHelper::ColTypes::INTEGER, false, true},
    {"speed_level", DBHelper::ColTypes::INTEGER, false, true},
    {"cost", DBHelper::ColTypes::NUMERIC, false, true},
};
