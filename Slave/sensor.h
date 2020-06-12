#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);
//    Sensor(const double degree = 25.0) : _degree(degree) {}
    double GetTemperature();

    void setTargetDegree(double target_degree);

    void setWindSpeed(int windspeed);

    void setIsWind(bool is_wind);

private:
    const double _d = 1.0;
    double _degree = 35.0;
    double _target_degree;
    int _windspeed;
    bool _is_wind;

    QTimer *_timer;
    QElapsedTimer *_elapsedtimer;
    const int _interval[4] = {25000, 20000, 15000, 10000};
    bool UpdateTemperature();

signals:
    void TemperatureChanged();

public slots:
    void SendTemperature();

};

#endif // SENSOR_H
