#include "dbaccess.h"
#include "common.h"
#include "database_defs.h"
#include "dbhelper.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QDateTime>

#include <set>
#include <thread>
#include <mutex>
#include <cassert>
#include <tuple>

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
    QString insert_sql = DBHelper::getInsertSQL(MasterUserContract::TITLE, MasterUserContract::COL_INFO);
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(insert_sql);
    QSqlError error = DBHelper::BindAndExec(q, {room_id, user_id, 0.0, 0.0});
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return false;
    }
    return true;
}

bool DBAccess::hasUser(const QString &room_id, const QString &user_id)
{
    QString kCountSql = "select count(*) from %1 where room = ? and id = ?;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kCountSql.arg(MasterUserContract::TITLE));
    auto error = DBHelper::BindAndExec(q, {room_id, user_id});
    if (error.type() == QSqlError::NoError)
    {
        if (!q.next())
        {
            qDebug() << q.lastError().text();
            return false;
        }
        return q.value(0).toBool();
    }
    qDebug() << error.text();
    return false;
}

bool DBAccess::delUser(const QString &room_id, const QString &user_id)
{
    const QString kDelSql = "delete from %1 where id = ? and room = ?;";;
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kDelSql.arg(MasterUserContract::TITLE));
    auto error = DBHelper::BindAndExec(q, {user_id, room_id});
    if (error.type() == QSqlError::NoError)
        return true;
    qDebug() << error.text();
    return false;
}

std::tuple<bool, double, double> DBAccess::getUseAndCost(const QString &room_id, const QString &user_id)
{
    const QString kSelSql = "select use, cost from %1 where id = ? and room = ?;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kSelSql.arg(MasterUserContract::TITLE));
    auto error = DBHelper::BindAndExec(q, {user_id, room_id});
    double use, cost;
    if (error.type() == QSqlError::NoError)
    {
        if (!q.next())
        {
            qDebug() << q.lastError().text();
            return {false, {}, {}};
        }
        use = q.value(0).toDouble();
        cost = q.value(1).toDouble();
        return {true, use, cost};
    }
    qDebug() << error.text();
    return {false, {}, {}};
}

std::pair<bool, std::vector<std::tuple<QString, QString, double, double> > > DBAccess::getUsers()
{
    const QString kSelSql = "select room, id, use, cost from %1;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kSelSql.arg(MasterPowerStatContract::TITLE));
    q.exec();

    QSqlError error = q.lastError();
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return {false, {}};
    }

    std::vector<std::tuple<QString, QString, double, double>> res;
    while (q.next())
    {
        QString room_id = q.value(0).toString();
        QString user_id = q.value(1).toString();
        double use = q.value(2).toDouble();
        double cost = q.value(3).toDouble();
        res.emplace_back(room_id, user_id, use, cost);
    }
    return {true, res};
}

bool DBAccess::hasManager(const QString &account, const QString &password)
{
    QString kCountSql = "select count(*) from %1 where account = ? and password = ?;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kCountSql.arg(MasterAuthContract::TITLE));
    auto error = DBHelper::BindAndExec(q, {account, password});
    if (error.type() == QSqlError::NoError)
    {
        if (!q.next())
        {
            qDebug() << q.lastError().text();
            return false;
        }
        return q.value(0).toBool();
    }
    qDebug() << error.text();
    qDebug() << q.lastQuery();
    qDebug() << q.executedQuery();
    return false;
}

bool DBAccess::addRoomPowerStat(const QString &room_id, bool is_starting_up)
{
    QString insert_sql = DBHelper::getInsertSQL(MasterPowerStatContract::TITLE, MasterPowerStatContract::COL_INFO);
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(insert_sql);
    QSqlError error = DBHelper::BindAndExec(q, {room_id, is_starting_up, QDateTime::currentSecsSinceEpoch()});
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return false;
    }
    return true;
}

std::pair<bool, std::vector<std::tuple<QString, bool, QDateTime>>> DBAccess::getRoomPowerStats(const QDateTime &from, const QDateTime &to)
{
    const QString kSelSql = "select room, is_start_up, time from %1 where time between ? and ?;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kSelSql.arg(MasterPowerStatContract::TITLE));
    QSqlError error = DBHelper::BindAndExec(q, {from.toSecsSinceEpoch(), to.toSecsSinceEpoch()});
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return {false, {}};
    }

    std::vector<std::tuple<QString, bool, QDateTime>> res;
    while (q.next())
    {
        QString room_id = q.value(0).toString();
        bool is_start_up = q.value(1).toBool();
        QDateTime time = q.value(2).toDateTime();
        res.emplace_back(room_id, is_start_up, time);
    }
    return {true, res};
}

bool DBAccess::addRoomRequestStat(const StatPayload &payload)
{
    QString insert_sql = DBHelper::getInsertSQL(MasterRequestStatContract::TITLE, MasterRequestStatContract::COL_INFO);
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(insert_sql);
    QSqlError error = DBHelper::BindAndExec(q, {payload.room_id,
                                            payload.init_temperature,
                                            payload.end_temperature,
                                            payload.start_time.toSecsSinceEpoch(),
                                            payload.end_time.toSecsSinceEpoch(),
                                            payload.speed_level,
                                            payload.cost});
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return false;
    }
    return true;
}

std::pair<bool, std::vector<StatPayload> > DBAccess::getRoomRequestStats(const QDateTime &from, const QDateTime &to)
{
    const QString kSelSql = "select * from %1 where time between ? and ?;";
    QSqlQuery q(QSqlDatabase::database(connection_name));
    q.prepare(kSelSql.arg(MasterRequestStatContract::TITLE));
    QSqlError error = DBHelper::BindAndExec(q, {from.toSecsSinceEpoch(), to.toSecsSinceEpoch()});
    if (error.type() != QSqlError::NoError)
    {
        qDebug() << error.text();
        return {false, {}};
    }

    std::vector<StatPayload> res;
    while (q.next())
    {
        QString room_id = q.value(0).toString();
        double init_temperature = q.value(1).toDouble();
        double end_temperature = q.value(2).toDouble();
        QDateTime start_time = q.value(3).toDateTime();
        QDateTime end_time = q.value(4).toDateTime();
        SpeedLevel speed_level = static_cast<SpeedLevel>(q.value(5).toInt());
        double cost = q.value(6).toDouble();
        res.push_back({room_id, init_temperature, end_temperature, start_time, end_time, speed_level, cost});
    }
    return {true, res};
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
        if (!tables.contains(MasterUserContract::TITLE))
            init_sqls.push_back(MasterUserContract::getCreateSql());
        if (!tables.contains(MasterAuthContract::TITLE))
            init_sqls.push_back(MasterAuthContract::getCreateSql());
        if (!tables.contains(MasterPowerStatContract::TITLE))
            init_sqls.push_back(MasterPowerStatContract::getCreateSql());
        if (!tables.contains(MasterRequestStatContract::TITLE))
            init_sqls.push_back(MasterRequestStatContract::getCreateSql());
    }

    error = DBHelper::ExecSQLs(init_sqls, connection_name);
    return error;
}


