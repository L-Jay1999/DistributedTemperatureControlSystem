#include "request_payload.h"

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
        {RequestType::SCHEDULE, "WindSchedule"},
        // {RequestType::TELL_LISTENER_PORT, "TellListenerPort"},
};

const QString &getTypeStr(const RequestType type)
{
    assert(kTypeStr.count(type));
    return kTypeStr.at(type);
}

QJsonObject RequestPayload::toQJsonObject() const
{
    assert(CheckParams());
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
    if (listen_port.has_value())
        obj.insert(kListenPortKey, listen_port.value());
    if (is_in_queue.has_value())
        obj.insert(kIsInQueueKey, is_in_queue.value());
    obj.insert(kSrcHostKey, source_host);
    obj.insert(kSrcPortKey, source_port);
    obj.insert(kTargetHostKey, target_host);
    obj.insert(kTargetPortKey, target_port);
    return obj;
}

void RequestPayload::fromQJsonObject(const QJsonObject &obj)
{
    assert(obj.contains(kTypeKey));
    type = static_cast<decltype(type)>(obj.value(kTypeKey).toInt());
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
        mode = static_cast<decltype(mode)::value_type>(obj.value(kModeKey).toInt());
    if (obj.contains(kSpeedLevel))
        speed_level = static_cast<decltype(speed_level)::value_type>(obj.value(kSpeedLevel).toInt());
    if (obj.contains(kUseKey))
        use = obj.value(kUseKey).toDouble();
    if (obj.contains(kCostKey))
        cost = obj.value(kCostKey).toDouble();
    if (obj.contains(kIsOpenKey))
        is_open = obj.value(kIsOpenKey).toBool();
    if (obj.contains(kListenPortKey))
        listen_port = static_cast<quint16>(obj.value(kListenPortKey).toInt());
    if (obj.contains(kSrcHostKey))
        source_host = obj.value(kSrcHostKey).toString();
    if (obj.contains(kSrcPortKey))
        source_host = static_cast<quint16>(obj.value(kSrcPortKey).toInt());
    if (obj.contains(kTargetHostKey))
        source_host = obj.value(kTargetHostKey).toString();
    if (obj.contains(kTargetPortKey))
        source_host = static_cast<quint16>(obj.value(kTargetPortKey).toInt());
    if (obj.contains(kIsInQueueKey))
        is_in_queue = obj.value(kIsInQueueKey).toBool();
    assert(CheckParams());
}

inline QString RequestPayload::toString() const
{
    return QString(QJsonDocument(toQJsonObject()).toJson());
}

inline QByteArray RequestPayload::toBase64ByteArray() const
{
    return QJsonDocument(toQJsonObject()).toJson().toBase64();
}

bool RequestPayload::CheckParams() const
{
    switch (type)
    {
    case RequestType::LOGIN:
        if (user_id.has_value() && room_id.has_value()
                && listen_port.has_value())
            return true;
        break;
    case RequestType::LOGIN_RESPONSE:
        if (result.has_value())
            if (!result.value() || (result.value() && config.has_value()))
                return true;
        break;
    case RequestType::ACK:
        if (result.has_value())
            return true;
        break;
    case RequestType::FORCE_SHUTDOWN:
        return true;
        break;
    case RequestType::GET_ROOM_TEMP:
        return true;
        break;
    case RequestType::GET_ROOM_TEMP_RESPONSE:
        if (temperature.has_value())
            return true;
        break;
    case RequestType::SET_MODE:
        if (mode.has_value())
            return true;
        break;
    case RequestType::SET_SPEED:
        if (room_id.has_value() && speed_level.has_value())
            return true;
        break;
    case RequestType::SET_TEMP:
        if (temperature.has_value() && room_id.has_value())
            return true;
        break;
    case RequestType::USE_AND_COST:
        if (use.has_value() && cost.has_value())
            return true;
        break;
    case RequestType::SHUTDOWN:
        if (room_id.has_value())
            return true;
        break;
    case RequestType::WIND:
        if (is_open.has_value() && room_id.has_value())
            return true;
        break;
    case RequestType::SCHEDULE:
        if (is_in_queue.has_value())
            return true;
        break;
    default:break;
    }
    return false;
}
