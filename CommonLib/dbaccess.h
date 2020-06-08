#ifndef DBACESS_H
#define DBACESS_H

#include <QSqlError>
#include <vector>
#include <utility>
#include <QDateTime>

#include "common.h"
/**
 * @brief The DBAccess class 使用前先设置用户类型
 */
struct StatPayload
{
    QString room_id{};
    double init_temperature{};
    double end_temperature{};
    quint64 start_time{};
    quint64 end_time{};
    SpeedLevel speed_level{};
    double cost{};
};

class DBAccess
{
public:
    DBAccess();
    bool isConnected() const;
    bool addUser(const QString &room_id, const QString &user_id);
    bool hasUser(const QString &room_id, const QString &user_id);
    bool delUser(const QString &room_id, const QString &user_id);
    std::pair<double, double> getUser(const QString &room_id, const QString &user_id);
    bool updateUseAndCost(const QString &room_id, const QString &user_id, double use, double cost);
    std::vector<std::pair<double, double>> getUsers();
    // bool addLog();
    // std::tuple<QString, LogLevel, QString> getLogs(const QDateTime &from, const QDateTime &to);
    bool hasManager(const QString &account, const QString &password);
    bool addRoomPowerStat(const QString &room_id, bool is_starting_up);
    std::tuple<QString, bool, QString> getRoomPowerStats(const QDateTime &from, const QDateTime &to);
    bool addRoomRequestStat(const StatPayload &payload);
    std::vector<StatPayload> getRoomRequestStats(const QDateTime &from, const QDateTime &to);
private:
    QSqlError init() const;
    bool is_inited = false;
    QString connection_name = "";
};

#endif // DBACESS_H
