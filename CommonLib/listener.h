#ifndef LISTENER_H
#define LISTENER_H

#include <map>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include "request_controller.h"
#include "request_payload.h"

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener(QObject *parent = nullptr) : QObject(parent), server(new QTcpServer(this))
    {
        connect(server, SIGNAL(QTcpServer::newConnection()), this, SLOT(PendConnection()));
    }

    // 调用此方法使 Listener 开始监听，绑定成功则返回 true，否则返回 false
    bool Listen(const quint16 port)
    {
        return server->listen(QHostAddress::LocalHost, port);
    }

    virtual ~Listener() {}

private:
    QTcpServer *server;
public slots:
    void PendConnection()
    {
        QTcpSocket *connection = server->nextPendingConnection();
        if (connection)
        {
            connect(connection, &QAbstractSocket::disconnected, connection, &QObject::deleteLater);
            if (!connection->waitForReadyRead())
            {
               qDebug() << connection->errorString();
               return;
            }

            auto receive_data = connection->readAll();

            auto response = RequestController::Request(receive_data);

            connection->write(response);
            if (!connection->waitForBytesWritten())
            {
                qDebug() << connection->errorString();
                return;
            }
        }
    }

};

#endif // LISTENER_H

