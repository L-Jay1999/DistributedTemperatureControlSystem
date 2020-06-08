#ifndef DBACESS_H
#define DBACESS_H

#include <QSqlError>

/**
 * @brief The DBAccess class 使用前先设置用户类型
 */
class DBAccess
{
public:
    DBAccess();
    bool isConnected() const;
private:
    QSqlError init() const;
    bool is_inited = false;
    QString connection_name = "";
};

#endif // DBACESS_H
