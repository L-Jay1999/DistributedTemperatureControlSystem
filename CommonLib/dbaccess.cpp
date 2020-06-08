#include "dbaccess.h"
#include "common.h"
#include "database_defs.h"

#include <QSqlDatabase>
#include <QDebug>

#include <set>
#include <thread>
#include <mutex>
#include <cassert>




DBAccess::DBAccess()
{
    connection_name = "QSQLITE_connection_" + QString().setNum(getHashedThreadId());
    if (!Config::hasUserType())
    {
        assert(false);
        qDebug() << "使用DBAcess前先设置用户类型";
        throw "使用DBAcess前先设置用户类型";
    }

    if (!isConnected())
    {
        auto error = init();
        if (error.type() == QSqlError::NoError)
            is_inited = true;
        else
            qDebug() << error.text();
    }
}

bool DBAccess::isConnected() const
{
    return QSqlDatabase::contains(connection_name);
}

bool DBAccess::addUser(const QString &room_id, const QString &user_id)
{
    return false;
}

QSqlError DBAccess::init() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    QSqlError error;
    db.setDatabaseName(Config::getDBPath());
    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    std::vector<QString> init_sqls;
    // 检查表是否已存在，若不存在则创建表
    if (Config::getUserType().value() == Config::UserType::MASTER)
    {
        if (!tables.contains(Log::TITLE))
            init_sqls.push_back(Log::getCreateSql());
        if (!tables.contains(MasterUser::TITLE))
            init_sqls.push_back(MasterUser::getCreateSql());
        if (!tables.contains(MasterAuth::TITLE))
            init_sqls.push_back(MasterAuth::getCreateSql());
        if (!tables.contains(MasterPowerStat::TITLE))
            init_sqls.push_back(MasterPowerStat::getCreateSql());
        if (!tables.contains(MasterRequestStat::TITLE))
            init_sqls.push_back(MasterRequestStat::getCreateSql());
    }
    else if (Config::getUserType().value() == Config::UserType::SLAVE)
    {
        if (!tables.contains(Log::TITLE))
            init_sqls.push_back(Log::getCreateSql());
    }

    error = DBHelper::ExecSQLs(init_sqls);
    return error;
}


