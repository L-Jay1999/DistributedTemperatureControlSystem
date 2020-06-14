#ifndef SHUTDOWNCONTROLLER_H
#define SHUTDOWNCONTROLLER_H

#include <QString>
#include <tuple>
#include <QDebug>
#include <QObject>

#include "requests.h"

class ShutDownController : public QObject
{
    Q_OBJECT

public:
    ShutDownController() = delete;
    explicit ShutDownController(QObject *parent = nullptr, const QString &RoomID = "");
    bool ShutDown();

private:
    QString _RoomID;

signals:
    void AddTextShutDown(QString s);
};

#endif // SHUTDOWNCONTROLLER_H
