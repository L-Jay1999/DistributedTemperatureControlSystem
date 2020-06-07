#ifndef DBACESS_H
#define DBACESS_H

#include <QSqlError>

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
