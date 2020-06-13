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
    LoginRequest() = delete;
    LoginRequest(const QString &user_id, const QString &room_id, const quint16 &listen_port)
        : user_id_(user_id), room_id_(room_id), listen_port_(listen_port)
    {}

    std::tuple<ErrorPack, bool, WorkingMode, double> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}, {}, {}};
        }
        else
        {
            if (response.type == RequestType::LOGIN_RESPONSE)
            {
                if (response.result)
                    return {errs, true, std::get<0>(response.config.value()), std::get<1>(response.config.value())};
                else
                    return {errs, false, {}, {}};
            }
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}, {}, {}};
            }
        }
    }

protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.user_id = user_id_;
        payload.room_id = room_id_;
        payload.target_host = Config::kMasterHostAddr;
        payload.target_port = Config::kMasterListenPort;
        payload.listen_port = listen_port_;
        return payload;
    }

private:
    QString user_id_{};
    QString room_id_{};
    quint16 listen_port_{};
};

class ShutDownRequest : Request
{
public:
    ShutDownRequest(const QString &room_id) : room_id_(room_id) {}

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SHUTDOWN;
        payload.room_id = room_id_;
        payload.target_host = Config::kMasterHostAddr;
        payload.target_port = Config::kMasterListenPort;
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SET_SPEED;
        payload.room_id = room_id_;
        payload.speed_level = speed_level_;
        payload.target_host = Config::kMasterHostAddr;
        payload.target_port = Config::kMasterListenPort;
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SET_TEMP;
        payload.room_id = room_id_;
        payload.temperature = temperature_;
        payload.target_host = Config::kMasterHostAddr;
        payload.target_port = Config::kMasterListenPort;
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::WIND;
        payload.room_id = room_id_;
        payload.is_open = is_open_;
        payload.target_host = Config::kMasterHostAddr;
        payload.target_port = Config::kMasterListenPort;
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
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

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
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

    std::pair<ErrorPack, double> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::GET_ROOM_TEMP_RESPONSE)
                return {errs, response.temperature.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
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

class ScheduleInfoRequest : Request
{
public:
    ScheduleInfoRequest(bool is_in_queue) : is_in_queue_(is_in_queue) {}

    std::pair<ErrorPack, bool> Send()
    {
        auto payload = BuildPayload();

        auto [errs, response] = SendRequest(payload);
        if (errs.hasError())
        {
            return {errs, {}};
        }
        else
        {
            if (response.type == RequestType::ACK)
                return {errs, response.result.value()};
            else
            {
                errs.has_parsing_error = true;
                errs.parsing_err_type = ParsingErrType::INVALID_DATA;
                return {errs, {}};
            }
        }
    }
protected:
    RequestPayload BuildPayload() override
    {
        RequestPayload payload{};
        payload.type = RequestType::SCHEDULE;
        payload.is_in_queue = is_in_queue_;
        return payload;
    }
private:
    bool is_in_queue_{};
};

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
