#ifndef DBDEF_BASE_H
#define DBDEF_BASE_H

#include <QString>
#include <QtSql/QSqlQuery>

#include <vector>
#include <variant>

#include "common.h"

namespace DBHelper
{
    enum class ColTypes
    {
        INTEGER,
        NUMERIC,
        TEXT
    };

    struct ColPayload
    {
        QString col_name{};
        ColTypes col_type{ColTypes::INTEGER};
        bool is_primary{false};
        bool is_not_null{false};
        bool has_default{false};
        QString default_val{""};
    };

    /**
     * @brief 通过给定信息构造建表语句
     * 
     * @param table_name 建表的名称
     * @param col_info 表的列信息
     * @return QString 建表语句
     */
    QString getCreateSQL(const QString &table_name, const std::vector<ColPayload> &col_info);

    /**
     * @brief 以事务的方式执行多个 SQL 语句
     * 
     * @param query_sqls 需要执行的 SQL 语句
     * @return QSqlError 错误信息
     */
    QSqlError ExecSQLs(const std::vector<QString> &query_sqls);

    /**
     * @brief 通过给定信息构建插入语句
     * 
     * @param table_name 需要插入的表名称
     * @param col_info 该表的列信息
     * @return QString 构造的插入语句
     */
    QString getInsertSQL(const QString &table_name, const std::vector<ColPayload> &col_info);

    /**
     * @brief 将给出的值绑定至给出的 QSqlQuery 上并执行
     * 
     * @param q 已绑定 SQL 语句的 QSqlQuery 对象
     * @param binds 需要绑定的值
     * @return QSqlError 错误信息
     */
    QSqlError BindAndExec(QSqlQuery &q, const std::vector<std::variant<QString, double, int, qint64, SpeedLevel>> binds);
}


#endif // DBDEF_BASE_H
