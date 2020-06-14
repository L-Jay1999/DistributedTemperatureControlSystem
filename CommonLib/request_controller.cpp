#include "request_controller.h"

#include "../Slave/gettemperaturecontroller.h"
#include "../Slave/modealtercontroller.h"
#include "../Slave/useandcostcontroller.h"
#include "../Slave/windcontrollerfromm.h"
#include "../Master/userlogincontroller.h"
#include "../Master/airsupplycontroller.h"

#include <optional>

namespace RequestController
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
            // Master to Slave
            case RequestType::FORCE_SHUTDOWN:
            {
                // UNINPLEMENTED
                break;
            }
            case RequestType::GET_ROOM_TEMP:
            {
                response.type = RequestType::GET_ROOM_TEMP_RESPONSE;
                GetTemperatureController *controller =
                        dynamic_cast<GetTemperatureController *>(Config::getSlaveControllerPointer(Config::SlaveControllerType::GET_TEMPERATURE));
                response.temperature = controller->get();
                break;
            }
            case RequestType::SET_MODE:
            {
                response.type = RequestType::ACK;
                ModeAlterController *controller =
                        dynamic_cast<ModeAlterController *>(Config::getSlaveControllerPointer(Config::SlaveControllerType::MODE_ALTER));
                controller->SetMode(request_parsed.mode.value());
                response.result = true;
                break;
            }
            case RequestType::USE_AND_COST:
            {
                response.type = RequestType::ACK;
                UseAndCostController *controller =
                        dynamic_cast<UseAndCostController *>(Config::getSlaveControllerPointer(Config::SlaveControllerType::USE_COST));
                controller->setUseandCost(request_parsed.use.value(), request_parsed.cost.value());
                response.result = true;
                break;
            }
            case RequestType::SCHEDULE:
            {
                response.type = RequestType::ACK;
                WindControllerFromM *controller =
                         dynamic_cast<WindControllerFromM *>(Config::getSlaveControllerPointer(Config::SlaveControllerType::WIND_SCHEDULE));
                controller->Set(request_parsed.is_in_queue.value());
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
