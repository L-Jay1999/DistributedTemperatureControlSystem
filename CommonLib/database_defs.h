#ifndef DATABASE_DEFS_H
#define DATABASE_DEFS_H

#include "dbhelper.h"
#include "common.h"

#include <QString>
#include <vector>

struct Log
{
    static constexpr auto TITLE = "log";
    static const std::vector<DBHelper::ColPayload> COL_INFO;
    static QString getCreateSql() { return DBHelper::getCreateSQL(TITLE, COL_INFO); }
};

struct MasterUser
{
    static constexpr auto TITLE = "user";
    static const std::vector<DBHelper::ColPayload> COL_INFO;
    static QString getCreateSql() { return DBHelper::getCreateSQL(TITLE, COL_INFO); }
};

struct MasterAuth
{
    static constexpr auto TITLE = "auth";
    static const std::vector<DBHelper::ColPayload> COL_INFO;
    static QString getCreateSql() { return DBHelper::getCreateSQL(TITLE, COL_INFO); }
};

struct MasterPowerStat
{
    static constexpr auto TITLE = "room_power_stat";
    static const std::vector<DBHelper::ColPayload> COL_INFO;
    static QString getCreateSql() { return DBHelper::getCreateSQL(TITLE, COL_INFO); }
};

struct MasterRequestStat
{
    static constexpr auto TITLE = "room_power_stat";
    static const std::vector<DBHelper::ColPayload> COL_INFO;
    static QString getCreateSql() { return DBHelper::getCreateSQL(TITLE, COL_INFO); }
};

#endif // DATABASE_DEFS_H
