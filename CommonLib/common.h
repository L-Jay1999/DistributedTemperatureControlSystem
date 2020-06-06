#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>

#include <optional>
#include <random>
#include <map>

enum class WorkingMode
{
    COLD = 0,
    HOT,
};

enum class SpeedLevel
{
    LOW = 0,
    MID,
    HIGH,
};

int getRandomInt(int low_bound, int up_bound);

namespace Config {

    // 标记主机的地址和端口，用于从控机发送请求给中央空调
    static constexpr const char *kMasterHostAddr = "localhost";
    static constexpr quint16 kMasterListenPort = 12345;

    // 设定传输失败时重传次数
    static constexpr int kRetryAttempt = 3;

    /**
     * @brief 获取 Listener 监听的端口
     * 
     * @return quint16 监听的端口值
     */
    static quint16 getSlaveListenerPortValue();

    /**
     * @brief 设定 Listener 监听的端口
     * 
     * @param port 监听的端口
     */
    static void setSlaveListenerPort(const quint16 port);

    /**
     * @brief 判断是否设定了 Listener 的端口
     * 
     * @return true 已设定
     * @return false 未设定，需要至少调用一次 setSlaveListenerPort(port)
     */
    static bool hasSlaveListenerPort();

    /**
     * @brief 将从控机与其地址和端口进行对应
     * 
     * @param room_id 从控机所在房间号
     * @param host_addr 该从控机的地址
     * @param port 该从控机监听的端口
     */
    static void addAddress(const QString &room_id, const QString &host_addr, const quint16 port);

    /**
     * @brief 返回给定房间号的地址和监听端口
     * 
     * @param room_id 从控机所在房间号
     * @return std::pair<bool, std::pair<QString, quint16>> 若存在该房间号对应的记录，则返回 {true, {room_id, port}}, 
     * 否则返回 {false, {}}
     */
    static std::pair<bool, std::pair<QString, quint16>> getAddress(const QString &room_id);
};
#endif // COMMON_H
