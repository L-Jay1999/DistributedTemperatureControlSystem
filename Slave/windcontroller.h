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
    explicit WindController(QObject *parent = nullptr);
    bool Send(const QString &RoomID, const bool open);

signals:
    void AddTextWind(QString s);
};

#endif // WINDCONTROLLER_H
