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

template <typename T>
inline constexpr int EnumToInt(const T enum_val)
{
    static_assert (std::is_enum<T>::value, "Type of T must be enum type.");
    return static_cast<int>(enum_val);
}

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
    // TELL_LISTENER_PORT,
    UB = WIND,
    LB = LOGIN,
    NIL = -1,
};

static inline const QString &getTypeStr(const RequestType type)
{
    static const std::map<RequestType, QString> kTypeStr =
    {
        {RequestType::LOGIN, "Login"},
        {RequestType::LOGIN_RESPONSE, "LoginResponse"},
        {RequestType::ACK, "Ack"},
        {RequestType::FORCE_SHUTDOWN, "ForceShutDown"},
        {RequestType::GET_ROOM_TEMP, "GetRoomTemperature"},
        {RequestType::GET_ROOM_TEMP_RESPONSE, "GetRoomTemperatureResponse"},
        {RequestType::SET_MODE, "SetMode"},
        {RequestType::SET_SPEED, "SetSpeed"},
        {RequestType::SET_TEMP, "SetTemperature"},
        {RequestType::USE_AND_COST, "UseAndCost"},
        {RequestType::SHUTDOWN, "ShutDown"},
        {RequestType::WIND, "Wind"},
        // {RequestType::TELL_LISTENER_PORT, "TellListenerPort"},
    };
    assert(kTypeStr.count(type));
    return kTypeStr.at(type);
}

struct RequestPayload
{
    static constexpr const char *kTypeKey = "type";
    static constexpr const char *kRoomIdKey = "room_id";
    static constexpr const char *kUserIdKey = "user_id";
    static constexpr const char *kResultKey = "result";
    static constexpr const char *kTemperatureKey = "temperature";
    static constexpr const char *kConfigKey = "config";
    static constexpr const char *kModeKey = "mode";
    static constexpr const char *kSpeedLevel = "speed_level";
    static constexpr const char *kUseKey = "use";
    static constexpr const char *kCostKey = "cost";
    static constexpr const char *kIsOpenKey = "is_open";
    // static constexpr const char *kListenerPortKey = "listener_port";

    RequestPayload() {}
    RequestPayload(const RequestType request_type) : type(request_type) {}
    QJsonObject ToQJsonObject() const
    {
        QJsonObject obj;
        obj.insert(kTypeKey, getTypeStr(type));
        if (result.has_value())
            obj.insert(kResultKey, result.value());
        if (temperature.has_value())
            obj.insert(kTemperatureKey, temperature.value());
        if (user_id.has_value())
            obj.insert(kUserIdKey, user_id.value());
        if (room_id.has_value())
            obj.insert(kRoomIdKey, room_id.value());
        if (config.has_value())
        {
            QJsonObject config_obj;
            const auto [default_mode, default_temp] = config.value();
            config_obj.insert(kModeKey, EnumToInt(default_mode));
            config_obj.insert(kTemperatureKey, default_temp);
            obj.insert(kTemperatureKey, config_obj);
        }
        if (mode.has_value())
            obj.insert(kModeKey, EnumToInt(mode.value()));
        if (speed_level.has_value())
            obj.insert(kSpeedLevel, EnumToInt(speed_level.value()));
        if (use.has_value())
            obj.insert(kUseKey, use.value());
        if (cost.has_value())
            obj.insert(kCostKey, cost.value());
        if (is_open.has_value())
            obj.insert(kIsOpenKey, is_open.value());
        // if (listener_port.has_value())
        //     obj.insert(kListenerPortKey, listener_port.value());
        return obj;
    }

    void FromQJsonObject(const QJsonObject &obj)
    {
        assert(obj.contains(kTypeKey));
        type = static_cast<decltype (type)>(obj.value(kTypeKey).toInt());
        if (obj.contains(kResultKey))
            result = obj.value(kResultKey).toBool();
        if (obj.contains(kTemperatureKey))
            temperature = obj.value(kTemperatureKey).toDouble();
        if (obj.contains(kUserIdKey))
            user_id = obj.value(kUserIdKey).toString();
        if (obj.contains(kRoomIdKey))
            room_id = obj.value(kRoomIdKey).toString();
        if (obj.contains(kConfigKey))
        {
            const auto &config_obj = obj.value(kConfigKey).toObject();
            assert(config_obj.contains(kModeKey));
            assert(config_obj.contains(kTemperatureKey));
            config = {static_cast<WorkingMode>(config_obj.value(kModeKey).toInt()), config_obj.value(kTemperatureKey).toDouble()};
        }
        if (obj.contains(kModeKey))
            mode = static_cast<decltype (mode)::value_type>(obj.value(kModeKey).toInt());
        if (obj.contains(kSpeedLevel))
            speed_level = static_cast<decltype (speed_level)::value_type>(obj.value(kSpeedLevel).toInt());
        if (obj.contains(kUseKey))
            use = obj.value(kUseKey).toDouble();
        if (obj.contains(kCostKey))
            cost = obj.value(kCostKey).toDouble();
        if (obj.contains(kIsOpenKey))
            is_open = obj.value(kIsOpenKey).toBool();
        // if (obj.contains(kListenerPortKey))
        //     listener_port = obj.value(kListenerPortKey).toString();
    }

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
    // std::optional<QString> listener_port{std::nullopt};

    QString target_host{};
    quint16 target_port{};
};

class RequestParser
{
public:
    static std::pair<bool, RequestPayload> Parse(const QByteArray &obj_str)
    {
        RequestPayload payload{};
        bool is_suc = true;
        QJsonParseError json_err;
        QJsonDocument document = QJsonDocument::fromJson(obj_str, &json_err);
        if (json_err.error == QJsonParseError::NoError && !document.isNull())
        {
            assert(document.isObject());
            payload.FromQJsonObject(document.object());
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
