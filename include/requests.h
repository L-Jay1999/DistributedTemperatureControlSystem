#ifndef REQUESTS_H
#define REQUESTS_H

#include <tuple>
#include <utility>

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_base.h"
#include "request_payload.h"
#include "common.h"

class LoginRequest : Request
{
public:
    LoginRequest(const QString &user_id, const QString &room_id)
        : user_id_(user_id), room_id_(room_id)
    {}

    std::tuple<bool, WorkingMode, double> Send()
    {
        auto payload = BuildPayload();
        bool is_parsing_suc = false;
        RequestPayload response{};
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [is_suc, temp_response] = RequestParser::Parse(SendRequest(payload));
            is_parsing_suc = is_suc;
            if (is_parsing_suc)
            {
                response = temp_response;
                break;
            }
        }
        if (is_parsing_suc)
            return {is_parsing_suc, std::get<0>(response.config.value()), std::get<1>(response.config.value())};
        return {is_parsing_suc, WorkingMode(), double()};
    }

protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.user_id = user_id_;
        payload.room_id = room_id_;
        payload.target_host = kMasterHostAddr;
        payload.target_port = kMasterListenPort;
        return payload;
    }

private:
    QString user_id_{};
    QString room_id_{};
};

class ShutDownRequest : Request
{
public:
    ShutDownRequest(const QString &room_id) : room_id_(room_id) {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SHUTDOWN;
        payload.room_id = room_id_;
        payload.target_host = kMasterHostAddr;
        payload.target_port = kMasterListenPort;
        return payload;
    }
private:
    QString room_id_{};
};

class SetSpeedRequest : Request
{
public:
    SetSpeedRequest(const QString &room_id, const SpeedLevel speed_level)
        : room_id_(room_id), speed_level_(speed_level)
    {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SET_SPEED;
        payload.room_id = room_id_;
        payload.speed_level = speed_level_;
        payload.target_host = kMasterHostAddr;
        payload.target_port = kMasterListenPort;
        return payload;
    }
private:
    QString room_id_{};
    SpeedLevel speed_level_{};
};

class SetTemperatureRequest : Request
{
public:
    SetTemperatureRequest(const QString &room_id, const double temperature)
        : room_id_(room_id), temperature_(temperature)
    {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SET_TEMP;
        payload.room_id = room_id_;
        payload.temperature = temperature_;
        payload.target_host = kMasterHostAddr;
        payload.target_port = kMasterListenPort;
        return payload;
    }
private:
    QString room_id_{};
    double temperature_{};
};

class WindRequest : Request
{
public:
    WindRequest(const QString &room_id, const bool is_open)
        : room_id_(room_id), is_open_(is_open)
    {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::WIND;
        payload.room_id = room_id_;
        payload.is_open = is_open_;
        payload.target_host = kMasterHostAddr;
        payload.target_port = kMasterListenPort;
        return payload;
    }
private:
    QString room_id_{};
    bool is_open_{};
};

class UseAndCostRequest : Request
{
public:
    UseAndCostRequest(const double use, const double cost)
        : use_(use), cost_(cost)
    {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::USE_AND_COST;
        payload.use = use_;
        payload.cost = cost_;
        return payload;
    }
private:
    double use_{};
    double cost_{};
};

class SetModeRequest : Request
{
public:
    SetModeRequest(const WorkingMode mode) : mode_(mode) {}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SET_MODE;
        payload.mode = mode_;
        return payload;
    }
private:
    WorkingMode mode_{};
};

class ForceShutDownRequest : Request
{
public:
    ForceShutDownRequest(){}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::FORCE_SHUTDOWN;
        return payload;
    }
private:
};

class GetRoomTemperatureRequest : Request
{
public:
    GetRoomTemperatureRequest(){}

    bool Send()
    {
        auto payload = BuildPayload();
        bool is_suc = false;
        for (int i = 0; i < kRetryAttempt; i++)
        {
            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
            if (temp_suc && response.type == RequestType::ACK && response.result)
            {
                is_suc = true;
                break;
            }
        }
        return is_suc;
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::GET_ROOM_TEMP;
        return payload;
    }
private:
};

//class TellListenerPortRequest : Request
//{
//public:
//    TellListenerPortRequest(const quint16 port): listener_port(port) {}

//    bool Send()
//    {
//        auto payload = BuildPayload();
//        bool is_suc = false;
//        for (int i = 0; i < kRetryAttempt; i++)
//        {
//            auto [temp_suc, response] = RequestParser::Parse(SendRequest(payload));
//            if (temp_suc && response.type == RequestType::ACK && response.result)
//            {
//                is_suc = true;
//                break;
//            }
//        }
//        return is_suc;
//    }
//protected:
//    RequestPayload BuildPayload() override
//    {
//        RequestPayload payload{};
//        payload.type = RequestType::TELL_LISTENER_PORT;
//        payload.listener_port = listener_port;
//        return payload;
//    }
//private:
//    quint16 listener_port;
//};

static inline RequestPayload getAckResponse(const bool result = true)
{
    RequestPayload ack_response;
    ack_response.type = RequestType::ACK;
    ack_response.result = result;
    return ack_response;
}

static inline RequestPayload getGetRoomTemperatureResponse(const double temperature)
{
    RequestPayload response;
    response.type = RequestType::GET_ROOM_TEMP_RESPONSE;
    response.temperature = temperature;
    return response;
}

static inline RequestPayload getLoginResponse(const bool result, const std::pair<WorkingMode, double> &config = std::pair<WorkingMode, double>{})
{
    RequestPayload response;
    response.type = RequestType::LOGIN_RESPONSE;
    response.result = result;
    if (result)
        response.config = config;
}

#endif // REQUESTS_H
