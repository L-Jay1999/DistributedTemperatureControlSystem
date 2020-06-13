#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QString>
#include "../CommonLib/common.h"

class Schedule : public QObject
{
    Q_OBJECT
public:
    explicit Schedule(QObject *parent = nullptr);
    void addRoom(const QString& RoomID,const Config::config& conf);
    void delRoom(const QString& RoomID);
signals:

public slots:
};

#endif // SCHEDULE_H
