#ifndef REQUEST_CONTROLLER_H
#define REQUEST_CONTROLLER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_payload.h"
#include "requests.h"

class RequestController
{
public:
    /**
     * @brief 接收 Listener 收到的请求，将其解析后分发给其他控制器，
     * 并将控制器处理的结果构造为响应返回给 Listener
     * 
     * @param request Listener 收到的响应
     * @param host_addr 连接发起者的 IP 地址
     * @param host_port 连接发起者的端口
     * @return QByteArray Base64编码后的响应
     */
    static QByteArray HandleRequest(const QByteArray &request, const QString &host_addr, const quint16 host_port)
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
            switch (request_parsed.type)
            {
            // Slave to Master
            case RequestType::LOGIN:break;
            case RequestType::SET_SPEED:break;
            case RequestType::SET_TEMP:break;
            case RequestType::SHUTDOWN:break;
            case RequestType::WIND:break;
            // Master to Slave
            case RequestType::FORCE_SHUTDOWN:break;
            case RequestType::GET_ROOM_TEMP:break;
            case RequestType::SET_MODE:break;
            case RequestType::USE_AND_COST:break;
            case RequestType::SCHEDULE:break;
            default:
                qDebug() << getTypeStr(request_parsed.type);
                assert(false);
                throw getTypeStr(request_parsed.type);
            }
        }

        return response.toBase64ByteArray();
    }
};

#endif // REQUEST_CONTROLLER_H
