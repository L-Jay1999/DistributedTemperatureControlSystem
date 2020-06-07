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
            return fail_response.toBase64ByteArray();
        }
        else
        {
            switch (request_parsed.type)
            {
                // ......
            }
        }

        return response.toBase64ByteArray();
    }
};

#endif // REQUEST_CONTROLLER_H
