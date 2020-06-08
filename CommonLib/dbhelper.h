#ifndef DBDEF_BASE_H
#define DBDEF_BASE_H

#include <QString>
#include <vector>
#include <QSqlQuery>

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

    QString getCreateSQL(const QString &table_name, const std::vector<ColPayload> &col_info);

    QSqlError ExecSQLs(const std::vector<QString> &query_sqls);

    QString getInsertSQL(const QString &table_name, const std::vector<ColPayload> &col_info);
}


#endif // DBDEF_BASE_H
