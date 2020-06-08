#include "database_defs.h"

const std::vector<DBHelper::ColPayload> Log::COL_INFO =
{
    {"time", DBHelper::ColTypes::INTEGER, false, true},
    {"level", DBHelper::ColTypes::INTEGER, false, true},
    {"content", DBHelper::ColTypes::TEXT, false, true},
};

const std::vector<DBHelper::ColPayload> MasterUser::COL_INFO =
{
    {"name", DBHelper::ColTypes::TEXT, false, false},
    {"room", DBHelper::ColTypes::TEXT, true, true},
    {"id", DBHelper::ColTypes::TEXT, true, true},
    {"use", DBHelper::ColTypes::NUMERIC, false, true},
    {"cost", DBHelper::ColTypes::NUMERIC, false, true},
};

const std::vector<DBHelper::ColPayload> MasterAuth::COL_INFO =
{
    {"account", DBHelper::ColTypes::TEXT, true, true},
    {"password", DBHelper::ColTypes::TEXT, false, true},
};

const std::vector<DBHelper::ColPayload> MasterPowerStat::COL_INFO =
{
    {"room", DBHelper::ColTypes::TEXT, false, true},
    {"is_start_up", DBHelper::ColTypes::INTEGER, false, true},
    {"time", DBHelper::ColTypes::INTEGER, false, true},
};

const std::vector<DBHelper::ColPayload> MasterRequestStat::COL_INFO =
{
    {"room", DBHelper::ColTypes::TEXT, false, true},
    {"initial_temperature", DBHelper::ColTypes::NUMERIC, false, true},
    {"target_temperature", DBHelper::ColTypes::NUMERIC, false, true},
    {"wind_level", DBHelper::ColTypes::INTEGER, false, true},
    {"cost", DBHelper::ColTypes::NUMERIC, false, true},
};
