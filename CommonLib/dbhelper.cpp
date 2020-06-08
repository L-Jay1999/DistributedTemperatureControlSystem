#include "dbhelper.h"

#include <QString>
#include <map>

#include <QSqlError>

namespace DBHelper
{
    static const std::map<ColTypes, QString> type_str =
    {
        {ColTypes::TEXT, "text"},
        {ColTypes::INTEGER, "integer"},
        {ColTypes::NUMERIC, "numeric"},
    };

    static inline const QString &getTypeStr(const ColTypes type)
    {
        return type_str.at(type);
    }

    QString getCreateSQL(const QString &table_name, const std::vector<ColPayload> &col_infos)
    {
        QString sql = "create table";
        sql.append(table_name)
                .append('(');
        bool has_primary_key = false;
        QString primary_keys = "primary key(";

        for (const auto info: col_infos)
        {
            sql.append(info.col_name + " ");
            sql.append(getTypeStr(info.col_type) + " ");
            if (info.is_primary)
            {
                has_primary_key = true;
                primary_keys.append(info.col_name + ",");
            }
            if (info.is_not_null)
                sql.append("not null ");
            if (info.has_default)
                sql.append(QString("default(%1)").arg(info.default_val));
            sql.append(",");
        }

        if (has_primary_key)
            primary_keys.back() = ')';

        sql.append(primary_keys + ",");
        sql.back() = ')';
        return sql;
    }

    QSqlError ExecSQLs(const std::vector<QString> &query_sqls)
    {
        QSqlDatabase::database().transaction();
        QSqlQuery q;
        for (const auto &sql : query_sqls)
        {
            if (!q.exec(sql))
            {
                QSqlDatabase::database().rollback();
                return q.lastError();
            }
        }
        QSqlDatabase::database().commit();
        return q.lastError();
    }

    QString getInsertSQL(const QString &table_name, const std::vector<ColPayload> &col_info)
    {
        const QString sql = "insert into %1 values (%2)";
        QString bind_str;
        for (const auto info : col_info)
            bind_str.append("?,");
        bind_str.remove()
    }

}
