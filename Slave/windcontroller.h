#ifndef WINDCONTROLLER_H
#define WINDCONTROLLER_H

#include <QString>
#include <tuple>
#include <QDebug>
#include <QObject>

#include "requests.h"
#include "common.h"

class WindController : public QObject
{
    Q_OBJECT

public:
    WindController() = delete;
    explicit WindController(QObject *parent = nullptr, const bool open = false, const QString &RoomID = "");
    bool Send();

private:
    bool _open;
    QString _RoomID;

signals:
    void AddTextWind(QString s);
};

#endif // WINDCONTROLLER_H
