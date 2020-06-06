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
    QByteArray SendRequest(const RequestPayload &payload)
    {
        QTcpSocket socket;
        QByteArray response;
        QJsonDocument document(payload.ToQJsonObject());
        socket.connectToHost(payload.target_host, payload.target_port);
        if (!socket.waitForConnected())
        {
            qDebug() << socket.errorString();
            return response;
        }
        socket.write(document.toJson());
        if (!socket.waitForBytesWritten())
        {
            qDebug() << socket.errorString();
            return response;
        }

        if (socket.waitForReadyRead())
            response = socket.readAll();
        else
        {
            qDebug() << socket.errorString();
            return response;
        }
        socket.disconnectFromHost();
        return response;
    }
};

#endif // REQUEST_BASE_H
