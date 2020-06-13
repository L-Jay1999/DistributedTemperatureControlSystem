#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <map>
#include <array>
#include <type_traits>
#include <cassert>
#include <optional>

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

#include "common.h"

enum class RequestType
{
    LOGIN = 0,
    LOGIN_RESPONSE,
    ACK,
    FORCE_SHUTDOWN,
    GET_ROOM_TEMP,
    GET_ROOM_TEMP_RESPONSE,
    SET_MODE,
    SET_SPEED,
    SET_TEMP,
    USE_AND_COST,
    SHUTDOWN,
    WIND,
    SCHEDULE,
    // TELL_LISTENER_PORT,
    UB = WIND,
    LB = LOGIN,
    NIL = -1,
};

const QString &getTypeStr(const RequestType type);

struct RequestPayload
{
    static constexpr auto kTypeKey = "type";
    static constexpr auto kRoomIdKey = "room_id";
    static constexpr auto kUserIdKey = "user_id";
    static constexpr auto kResultKey = "result";
    static constexpr auto kTemperatureKey = "temperature";
    static constexpr auto kConfigKey = "config";
    static constexpr auto kModeKey = "mode";
    static constexpr auto kSpeedLevel = "speed_level";
    static constexpr auto kUseKey = "use";
    static constexpr auto kCostKey = "cost";
    static constexpr auto kIsOpenKey = "is_open";
    static constexpr auto kSrcHostKey = "source_host";
    static constexpr auto kSrcPortKey = "source_port";
    static constexpr auto kTargetHostKey = "target_host";
    static constexpr auto kTargetPortKey = "target_port";
    static constexpr auto kListenPortKey = "listen_port";
    static constexpr auto kIsInQueueKey = "is_in_queue";

    RequestPayload() {}
    RequestPayload(const RequestType request_type) : type(request_type) {}
    RequestPayload(const QJsonObject json_obj) { fromQJsonObject(json_obj); }
    
    /**
     * @brief 将对应的 QJsonObject 对象转换为 RequestPayload 并原地存储
     * 
     * @param obj 需要转换的 QJsonObject 对象
     */
    void fromQJsonObject(const QJsonObject &obj);

    /**
     * @brief 将 RequestPayload 对象转换为 JSON 字符串
     * 
     * @return QString 转换得到的 JSON 字符串
     */
    QString toString() const;

    /**
     * @brief 将 RequestPayload 对象转换为 JSON 二进制序列(Base64编码)
     * 
     * @return QString 转换得到的 JSON 二进制序列(Base64编码)
     */
    QByteArray toBase64ByteArray() const;


    RequestType type{RequestType::NIL};
    std::optional<bool> result{std::nullopt};
    std::optional<double> temperature{std::nullopt};
    std::optional<QString> user_id{std::nullopt};
    std::optional<QString> room_id{std::nullopt};
    std::optional<std::tuple<WorkingMode, double>> config{std::nullopt};
    std::optional<WorkingMode> mode{std::nullopt};
    std::optional<SpeedLevel> speed_level{std::nullopt};
    std::optional<double> use{std::nullopt};
    std::optional<double> cost{std::nullopt};
    std::optional<bool> is_open{std::nullopt};
    std::optional<quint16> listen_port{std::nullopt};
    std::optional<bool> is_in_queue{std::nullopt};

    // 对于发送者只需要填写 target_host 和 target_port 字段，由接收方填写 source_host 和 source_port
    QString source_host{};
    quint16 source_port{};
    QString target_host{};
    quint16 target_port{};
private:
    /**
     * @brief 将 RequestPayload 对象转换成 QJsonObject 对象
     * 
     * @return QJsonObject 
     */
    QJsonObject toQJsonObject() const;

    /**
     * @brief 根据 type 的类型检查参数是否满足其格式规定
     * 
     * @return true 
     * @return false 
     */
    bool CheckParams() const;
};

class RequestParser
{
public:
    /**
     * @brief 将收到的以Base64编码的QByteArray解析成RequestPayload
     * 
     * @param obj_str 收到的以Base64编码的QByteArray
     * @return std::pair<bool, RequestPayload> pair<是否解析成功, 若解析成功则为解析结果>
     */
    static std::pair<bool, RequestPayload> ParseBase64(const QByteArray &obj_str)
    {
        return Parse(QByteArray::fromBase64(obj_str));
    }

    /**
     * @brief 将收到的QByteArray解析成RequestPayload
     * 
     * @param obj_str 收到的QByteArray
     * @return std::pair<bool, RequestPayload> pair<是否解析成功, 若解析成功则为解析结果>
     */
    static std::pair<bool, RequestPayload> Parse(const QByteArray &obj_str)
    {
        RequestPayload payload{};
        bool is_suc = true;
        QJsonParseError json_err;
        QJsonDocument document = QJsonDocument::fromJson(obj_str, &json_err);

        if (json_err.error == QJsonParseError::NoError && !document.isNull())
        {
            assert(document.isObject());
            payload.fromQJsonObject(document.object());
        }
        else
        {
            is_suc = false;
            qDebug() << json_err.errorString();
        }
        return {is_suc, payload};
    }
};

#endif // REQUEST_PARSER_H
