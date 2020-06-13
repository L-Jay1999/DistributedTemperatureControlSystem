#include <QVariant>
#include <QString>
#include <QDebug>
#include <QSqlError>

#include <variant>
#include <map>

#include "common.h"
#include "dbhelper.h"

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
        QString sql = "create table ";
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
        {
            primary_keys.back() = ')';
            sql.append(primary_keys + ",");
        }

        sql.back() = ')';
        return sql;
    }

    QSqlError ExecSQLs(const std::vector<QString> &query_sqls, const QString &connection_name)
    {
        QSqlDatabase db = QSqlDatabase::database(connection_name);
        qDebug() << db.isOpen();
        db.transaction();
        QSqlQuery q(db);
        for (const auto &sql : query_sqls)
        {
            qDebug() << sql;
            if (!q.exec(sql))
            {
                db.rollback();
                return q.lastError();
            }
        }
        db.commit();
        return q.lastError();
    }

    QString getInsertSQL(const QString &table_name, const std::vector<ColPayload> &col_info)
    {
        const QString sql = "insert into %1 values (%2)";
        QString bind_str;
        for (const auto info : col_info)
            bind_str.append("?,");
        bind_str.remove(bind_str.length() - 1, 1);
        return sql.arg(table_name).arg(bind_str);
    }

    QSqlError BindAndExec(QSqlQuery &q, const std::vector<std::variant<QString, double, int, SpeedLevel, qint64>> vals)
    {
        QSqlError error;
        for (auto val : vals)
        {
            if (std::holds_alternative<QString>(val))
                q.addBindValue(std::get<QString>(val));
            else if (std::holds_alternative<double>(val))
                q.addBindValue(std::get<double>(val));
            else if (std::holds_alternative<int>(val))
                q.addBindValue(std::get<int>(val));
            else if (std::holds_alternative<SpeedLevel>(val))
                q.addBindValue(EnumToInt(std::get<SpeedLevel>(val)));
            else if (std::holds_alternative<qint64>(val))
                q.addBindValue(std::get<qint64>(val));
            else
            {
                assert(false);
                qDebug() << "输入的值类型不正确";
                throw "STOP!";
            }
        }
        q.exec();
        return q.lastError();
    }

}
