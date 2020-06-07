#include "dbaccess.h"

#include <QSqlDatabase>
#include <QDebug>

#include <set>
#include <thread>
#include <mutex>
#include <cassert>

#include "common.h"

DBAccess::DBAccess()
{
    connection_name = "QSQLITE_connection_" + QString().setNum(getHashedThreadId());
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

QSqlError DBAccess::init() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    db.setDatabaseName(Config::kDBPath);
    if (!db.open())
        return db.lastError();

    // TODO 检查表是否已存在，若不存在则创建表

}
