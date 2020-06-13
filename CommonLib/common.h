#ifndef COMMON_H
#define COMMON_H

#include <QtGlobal>
#include <QtCore>

#include <optional>
#include <random>
#include <map>
#include <type_traits>
#include <thread>
#include <sstream>

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

/**
 * @brief 获取位于区间 [a, b] 内的随机整数
 * 
 * @tparam T 整数类型，不须填入，自动推导即可
 * @param a 区间下界
 * @param b 区间上界
 * @return T 生成的随机整数
 */
template<typename T>
inline T getRandomInt(T a, T b)
{
    static_assert(std::is_integral<T>::value, "getRandomInt 的参数类型必须是整数类型");
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution gen(a, b);
    return gen(rng);
}

/**
 * @brief 将枚举类型转换为对应的整形值
 * 
 * @tparam T 枚举类型，自动推导即可
 * @param enum_val 需要转换的枚举类型值
 * @return constexpr int 对应的整形值
 */
template <typename T>
inline constexpr int EnumToInt(const T enum_val)
{
    static_assert (std::is_enum<T>::value, "EnumToInt 的参数类型必须是枚举类型");
    return static_cast<int>(enum_val);
}

/**
 * @brief 获取当前线程ID哈希之后的值
 * @return 哈希值
 */
inline std::size_t getHashedThreadId()
{
     return std::hash<std::thread::id>()(std::this_thread::get_id());
}

/**
 * @brief 将当前线程ID转为字符串
 * @return 线程ID字符串
 */
inline QString getThreadIdStr()
{
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return QString::fromStdString(ss.str());
}

/**
 * @brief 获取指定长度的随机字符串(a-z范围内)
 * @param length 随机字符串的长度
 * @return 随机字符串
 */
QString getRandomString(int length);

namespace Config {

    // 标记主机的地址和端口，用于从控机发送请求给中央空调
    static constexpr auto kMasterHostAddr = "localhost";
    static constexpr quint16 kMasterListenPort = 12345;

    // 设定传输失败时重传次数
    static constexpr int kRetryAttempt = 3;

    enum class UserType
    {
        MASTER = 0,
        SLAVE,
    };

    enum class SlaveControllerType
    {
        USE_COST = 0,
        MODE_ALTER,
        GET_TEMPERATURE,
        FORCE_SHUTDOWN,
        WIND_SCHEDULE,
    };

    enum class MasterControllerType
    {
        LOGIN = 0,
        SET_SPEED,
        SET_TEMP,
        SHUTDOWN,
        WIND_REQUEST
    };

    /**
     * @brief 获取 Listener 监听的端口
     * 线程安全
     * @return quint16 监听的端口值
     */
    quint16 getSlaveListenerPortValue();

    /**
     * @brief 设定 Listener 监听的端口
     * 线程安全
     * @param port 监听的端口
     */
    void setSlaveListenerPort(const quint16 port);

    /**
     * @brief 判断是否设定了 Listener 的端口
     * 线程安全
     * @return true 已设定
     * @return false 未设定，需要至少调用一次 setSlaveListenerPort(port)
     */

    void clearSlaveListenerPort();

    bool hasSlaveListenerPort();

    /**
     * @brief 将从控机与其地址和端口进行对应
     * 线程安全
     * @param room_id 从控机所在房间号
     * @param host_addr 该从控机的地址
     * @param port 该从控机监听的端口
     */
    void addAddress(const QString &room_id, const QString &host_addr, const quint16 port);

    /**
     * @brief 返回给定房间号的地址和监听端口
     * 线程安全
     * @param room_id 从控机所在房间号
     * @return std::pair<bool, std::pair<QString, quint16>> 若存在该房间号对应的记录，则返回 {true, {room_id, port}}, 
     * 否则返回 {false, {}}
     */
    std::pair<bool, std::pair<QString, quint16>> getAddress(const QString &room_id);

    /**
     * @brief 设定当前使用者的类型
     * 线程安全
     * @param user_type 使用者的类型，MASTER 和 SLAVE 中的一个
     */
    void setUserType(const UserType user_type);

    /**
     * @brief 获取当前使用者类型
     * 线程安全
     * @return std::optional<UserType> 
     */
    std::optional<UserType> getUserType();

    /**
     * @brief 判断是否指定了用户类型
     * 线程安全
     * @return true 
     * @return false 
     */
    bool hasUserType();

    /**
     * @brief 获取数据库路径，只有在设置了用户类型后才会返回对应路径，否则返回空字符串
     * @return 数据库路径
     */
    QString getDBPath();

    void setSlaveControllerPointer(SlaveControllerType type, QObject *controller);

    QObject *getSlaveControllerPointer(SlaveControllerType ctrller_type);

    void setMasterControllerPointer(MasterControllerType type, QObject *controller);

    QObject *getMasterControllerPointer(MasterControllerType ctrller_type);

    void setTimeOutMsec(int timeout_ms);

    int getTimeOutMSec();

};
#endif // COMMON_H
