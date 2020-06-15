#ifndef LISTENER_H
#define LISTENER_H

#include <map>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include "master_request_controller.h"
#include "request_payload.h"
#include "common.h"


class Listener : public QObject
{
    Q_OBJECT

public:
    Listener(QObject *parent = nullptr) : QObject(parent), server(new QTcpServer(this))
    {
        connect(server, SIGNAL(newConnection()), this, SLOT(HandleConnection()));
    }

    /**
     * @brief 使 Listener 监听位于区间 [a,b] 内的随机端口
     *
     * @param a 区间下界
     * @param b 区间上界
     * @return quint16 成功监听的端口
     */
    quint16 ListenOnRandomPort(const quint16 a, const quint16 b)
    {
        int random_port = getRandomInt(a, b);
        // TODO 如果区间过小可能导致死循环，考虑之后缓减
        while (!Listen(random_port))
            random_port = getRandomInt(a, b);
        _port = random_port;
        server->close();
        Config::setSlaveListenerPort(random_port);
        return random_port;
    }

    /**
     * @brief 使 Listener 监听指定端口（默认为中央空调监听端口）
     *
     * @param port 需要监听的端口
     * @return true 成功监听
     * @return false 发生错误，监听失败
     */
    bool Listen(const quint16 port = Config::kMasterListenPort)
    {
        _port = port;
        return true;

        bool is_listen_suc = server->listen(QHostAddress::LocalHost, port);
        if (is_listen_suc)
            Config::setSlaveListenerPort(port);
        return is_listen_suc;
    }

    ~Listener() {}

private:
    QTcpServer *server;
    quint16 _port;
public slots:
    void StartListen()
    {
        qDebug() << "Start Listen " << this->thread();
        server->listen(QHostAddress::LocalHost, _port);
    }

    void StopListen()
    {
        server->close();
    }

    void HandleConnection()
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
            auto host_addr = connection->peerAddress().toString();
            auto host_port = connection->peerPort();
            auto response = MasterRequestController::HandleRequest(receive_data, host_addr, host_port);

            // TODO retransmission ?
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

