#ifndef SENSOR_H
#define SENSOR_H

#include "common.h"

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);

    double GetTemperature();

    void setIsWindWithoutUpdate(bool is_wind);

    void setTargetDegreeWithoutUpdate(double target_degree);

    void setTargetDegree(double target_degree);

    void setWindSpeed(SpeedLevel windspeed);

    void setIsWind(bool is_wind);

    void setWorkingMode(WorkingMode mode);

private:
    void StartTimer();

    void UpdateTemperature();
    std::recursive_mutex sensor_set_mtx{};
    std::recursive_mutex sensor_update_mtx{};
    static const std::map<SpeedLevel, double> kTempChangePerSecWind;
    static constexpr double kTempChangePerSecRoom = 1.0 / 10.0;
    static constexpr int kDefaultTimerInterval = 1000;

    double _room_init_degree = 27.0;
    double _current_degree{27.0};
    double _target_degree{};
    SpeedLevel _speed{};
    WorkingMode _mode{WorkingMode::COLD};
    bool _is_wind{false};

    QTimer _timer{};
    qint64 _last_update_time{};

signals:
    void reachTargetDegree();
    void higherThanTargetDegreePlusOne();
public slots:
    void TimerUp();
};

#endif // SENSOR_H
