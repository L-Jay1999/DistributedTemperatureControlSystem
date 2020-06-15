#ifndef REQUEST_BASE_H
#define REQUEST_BASE_H

#include <QTcpSocket>
#include <QByteArray>
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_payload.h"
#include "common.h"
#include "log.h"

enum class ParsingErrType
{
    FAILED_TO_PARSE,
    INVALID_DATA
};

struct ErrorPack
{
    ErrorPack() {}
    bool has_connection_error{false};
    QAbstractSocket::SocketError err_type{};
    QString err_str{};
    bool has_parsing_error{false};
    ParsingErrType parsing_err_type;

    bool hasError() const { return has_parsing_error || has_connection_error; }
    void setConnectionError(const QString &err_str, QAbstractSocket::SocketError err_type)
    {
        has_connection_error = true;
        this->err_str = err_str;
        this->err_type = err_type;
    }
    void setParsingError(ParsingErrType parsing_err_type)
    {
        this->parsing_err_type = parsing_err_type;
    }
};

struct RequestSendReturnPack
{
    ErrorPack err;
    RequestPayload response_payload{};
};

class Request
{
public:
protected:
    virtual RequestPayload BuildPayload() = 0;

    /**
     * @brief 根据提供的 payload 构造并发送请求（Base64编码）
     * 
     * @param payload 提供的 payload
     * @return QByteArray 返回响应
     */
    RequestSendReturnPack SendRequest(const RequestPayload &payload)
    {
        QTcpSocket socket;
        QByteArray response_base64;
        QByteArray send_data = payload.toBase64ByteArray();
        RequestSendReturnPack res;
        Log::addLog(Log::LogLevel::ERROR, QString("SEND: ") + payload.toString());
        socket.connectToHost(payload.target_host, payload.target_port);
        if (!socket.waitForConnected(Config::getTimeOutMSec()))
        {
            qDebug() << socket.errorString();
            res.err.setConnectionError(socket.errorString(), socket.error());
            return res;
        }
        socket.write(send_data);
        if (!socket.waitForBytesWritten(Config::getTimeOutMSec()))
        {
            qDebug() << socket.errorString();
            res.err.setConnectionError(socket.errorString(), socket.error());
            return res;
        }

        if (!socket.waitForReadyRead(Config::getTimeOutMSec()))
        {
            qDebug() << socket.errorString();
            res.err.setConnectionError(socket.errorString(), socket.error());
            return res;
        }
        response_base64 = socket.readAll();
        socket.disconnectFromHost();
        auto [is_parsed, response_payload] = RequestParser::ParseBase64(response_base64);
        if (!is_parsed)
        {
            res.err.setParsingError(ParsingErrType::FAILED_TO_PARSE);
            return res;
        }
        Log::addLog(Log::LogLevel::ERROR, QString("RECEIVE: ") + response_payload.toString());
        qDebug() << response_payload.toString();

        // add source host addr and port
        response_payload.source_host = payload.target_host;
        response_payload.source_port = payload.target_port;
        res.response_payload = response_payload;
        return res;
    }
};

#endif // REQUEST_BASE_H
