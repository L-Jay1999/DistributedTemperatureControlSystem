#ifndef REQUEST_BASE_H
#define REQUEST_BASE_H

#include <QTcpSocket>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_payload.h"
#include "common.h"

class Request
{
protected:
    virtual RequestPayload BuildPayload() = 0;
    /**
     * @brief 根据提供的 payload 构造并发送请求（Base64编码）
     * 
     * @param payload 提供的 payload
     * @return QByteArray 返回响应
     */
    std::pair<bool, RequestPayload> SendRequest(const RequestPayload &payload)
    {
        QTcpSocket socket;
        QByteArray response_base64;
        QByteArray send_data = payload.toBase64ByteArray();
        socket.connectToHost(payload.target_host, payload.target_port);
        if (!socket.waitForConnected())
        {
            qDebug() << socket.errorString();
            return {false, RequestPayload()};
        }

        socket.write(send_data);
        if (!socket.waitForBytesWritten())
        {
            qDebug() << socket.errorString();
            return {false, RequestPayload()};
        }

        if (!socket.waitForReadyRead())
        {
            qDebug() << socket.errorString();
            return {false, RequestPayload()};
        }
        response_base64 = socket.readAll();
        socket.disconnectFromHost();

        auto [is_parsed, response_payload] = RequestParser::ParseBase64(response_base64);
        if (!is_parsed)
            return {false, RequestPayload()};

        // add source host addr and port
        response_payload.source_host = payload.target_host;
        response_payload.source_port = payload.target_port;
        return {true, response_payload};
    }
};

#endif // REQUEST_BASE_H
