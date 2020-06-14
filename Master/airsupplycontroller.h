#ifndef AIRSUPPLYCONTROLLER_H
#define AIRSUPPLYCONTROLLER_H

#include <QObject>

class AirSupplyController : public QObject
{
    Q_OBJECT
public:
    explicit AirSupplyController(QObject *parent = nullptr);
    void UpdateAirSupply(bool OpenorClose, const QString &RoomID);
signals:

public slots:
};

#endif // AIRSUPPLYCONTROLLER_H
