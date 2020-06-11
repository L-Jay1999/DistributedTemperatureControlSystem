#ifndef DBACESS_H
#define DBACESS_H

#include <QSqlError>
#include <QDateTime>

#include <utility>
#include <vector>
#include <tuple>

#include "common.h"

struct StatPayload
{
    QString room_id{};
    double init_temperature{};
    double end_temperature{};
    QDateTime start_time{};
    QDateTime end_time{};
    SpeedLevel speed_level{};
    double cost{};
};

// 使用前先设置用户类型
class DBAccess
{
public:
    /**
     * @brief Construct a new DBAccess object
     * 根据线程ID建立数据库连接，使用之前会根据用户的类型选择打开的数据库路径，同时在
     * 数据库内建表（如果表不存在）
     */
    DBAccess();

    /**
     * @brief 判断是否与数据库建立连接
     */
    bool isConnected() const;

    /**
     * @brief 向 master.user 表中插入一个用户
     * 
     * @param room_id 房间号
     * @param user_id 用户身份证号
     * @return true 插入成功
     * @return false 插入失败，失败信息输出在命令行中
     */
    bool addUser(const QString &room_id, const QString &user_id);

    /**
     * @brief 判断 master.user 表中是否存在给定用户
     * 
     * @param room_id 房间号
     * @param user_id 用户身份证号
     * @return true 存在该用户
     * @return false 不存在该用户或发生错误，错误信息输出在命令行中
     */
    bool hasUser(const QString &room_id, const QString &user_id);

    /**
     * @brief 从 master.user 表中删除给定用户
     * 
     * @param room_id 房间号
     * @param user_id 用户身份证号
     * @return true 成功删除给定用户
     * @return false 删除用户失败或者发生错误，错误信息输出在命令行中
     */
    bool delUser(const QString &room_id, const QString &user_id);

    /**
     * @brief 获取给定用户的用量和消费金额
     * 
     * @param room_id 房间号
     * @param user_id 用户身份证号
     * @return std::tuple<bool, double, double> 分别表示获取是否成功，用量和消费金额
     */
    std::tuple<bool, double, double> getUseAndCost(const QString &room_id, const QString &user_id);

    /**
     * @brief 更新给定用户的用量和消费金额
     * 
     * @param room_id 房间号
     * @param user_id 用户身份证号
     * @param use 更新的用量
     * @param cost 更新的消费金额
     * @return true 更新成功
     * @return false 发生错误，错误信息输出在命令行中
     */
    bool updateUseAndCost(const QString &room_id, const QString &user_id, double use, double cost);

    /**
     * @brief 获取所有存在于 master.user 表内的用户
     * 
     * @return std::pair<bool, std::vector<std::tuple<QString, QString, double, double>>> 
     * 第一个分量表示是否成功，* 第二个包含用户所有信息，分别为 <房间号，身份证号，用量，消费金额>
     */
    std::pair<bool, std::vector<std::tuple<QString, QString, double, double>>> getUsers();
    // bool addLog();
    // std::tuple<QString, LogLevel, QString> getLogs(const QDateTime &from, const QDateTime &to);

    /**
     * @brief 查询 master.auth 表，判断是否存在给定管理人员
     * 
     * @param account 管理人员账户名
     * @param password 账户密码
     * @return true 存在给定的管理人员
     * @return false 不存在或密码错误或者发生错误
     */
    bool hasManager(const QString &account, const QString &password);

    /**
     * @brief 向 master.room_power_stat 表中插入一条记录，记录从控机开关机的时间
     * 
     * @param room_id 房间号
     * @param is_starting_up true 表示开机，false 表示关机
     * @return true 插入记录成功
     * @return false 插入记录失败，错误信息输出在命令行中
     */
    bool addRoomPowerStat(const QString &room_id, bool is_starting_up);

    /**
     * @brief 查询 master.room_power_stat 表，获取给定时间段内所有开关机记录
     * 
     * @param from 从该时间开始
     * @param to 到该时间截止
     * @return std::pair<bool, std::vector<std::tuple<QString, bool, QDateTime>>> 
     * 第一个分量表示查询是否成功，
     * 第二个分量为返回的记录，表示 <房间号，是否为开机，发生该事件的时间>
     */
    std::pair<bool, std::vector<std::tuple<QString, bool, QDateTime>>> getRoomPowerStats(const QDateTime &from, const QDateTime &to);
    
    /**
     * @brief 向 master.room_request_stat 表中插入一条数据，
     * 记录一个送风请求的信息（指从中央空调开始为从控机送风开始，到从控机发出停止送风请求，或者中央空调由于负载均衡停止为从控机送风为止）
     * 
     * @param payload 表示该请求的所有信息
     * @return true 添加记录成功
     * @return false 添加记录失败
     */
    bool addRoomRequestStat(const StatPayload &payload);

    /**
     * @brief 查询 master.room_request_stat 表，获取给定时间段内所有送风记录
     * 
     * @param from 从该时间开始
     * @param to 到该事件截止
     * @return std::pair<bool, std::vector<StatPayload>> 分别表示查询是否成功和送风记录
     */
    std::pair<bool, std::vector<StatPayload>> getRoomRequestStats(const QDateTime &from, const QDateTime &to);
private:
    QSqlError init() const;
    bool is_inited = false;
    QString connection_name = "";
};

#endif // DBACESS_H
