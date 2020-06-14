#include "master_request_controller.h"

#include "../Master/userlogincontroller.h"
#include "../Master/airsupplycontroller.h"

#include <optional>

namespace MasterRequestController
{
    QByteArray HandleRequest(const QByteArray &request, const QString &host_addr, const quint16 host_port)
    {
        RequestPayload response;

        auto [is_parsing_suc, request_parsed] = RequestParser::Parse(request);
        if (!is_parsing_suc)
        {
            auto fail_response = getAckResponse(false);
            fail_response.target_host = host_addr;
            fail_response.target_port = host_port;
            fail_response.source_host = request_parsed.target_host;
            fail_response.source_port = request_parsed.target_port;
            return fail_response.toBase64ByteArray();
        }
        else
        {
            response.target_host = host_addr;
            response.target_port = host_port;
            response.source_host = request_parsed.target_host;
            response.source_port = request_parsed.target_port;
            switch (request_parsed.type)
            {
            // Slave to Master
            case RequestType::LOGIN:
            {
                response.type = RequestType::LOGIN_RESPONSE;
                UserLoginController *controller =
                        dynamic_cast<UserLoginController *>(Config::getMasterControllerPointer(Config::MasterControllerType::LOGIN));
                auto [login_result, init_mode, init_temp] = controller->UserLogin(request_parsed.user_id.value(), request_parsed.room_id.value());
                response.result = login_result;
                response.config = {init_mode, init_temp};
                break;
            }
            case RequestType::SET_SPEED:
            {
                break;
            }
            case RequestType::SET_TEMP:
                break;
            case RequestType::SHUTDOWN:
                break;
            case RequestType::WIND:
            {
                response.type = RequestType::ACK;
                AirSupplyController *controller =
                        dynamic_cast<AirSupplyController *>(Config::getMasterControllerPointer(Config::MasterControllerType::WIND_REQUEST));
                response.result = true;
                break;
            }
            default:
                qDebug() << getTypeStr(request_parsed.type);
                assert(false);
                throw getTypeStr(request_parsed.type);
            }
        }

        return response.toBase64ByteArray();
    }
} // namespace RequestController
