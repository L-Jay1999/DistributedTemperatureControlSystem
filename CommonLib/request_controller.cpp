#include "request_controller.h"

#include "../Slave/gettemperaturecontroller.h"
#include "../Slave/modealtercontroller.h"
#include "../Slave/useandcostcontroller.h"

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
                break;
            case RequestType::SET_SPEED:
                break;
            case RequestType::SET_TEMP:
                break;
            case RequestType::SHUTDOWN:
                break;
            case RequestType::WIND:
                break;
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
                // TODO
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
