#ifndef SENSOR_H
#define SENSOR_H


class Sensor
{
public:
    Sensor() = delete;
    Sensor(const double degree = 25.0) : _degree(degree) {}
    double GetTemperature(double target);

private:
    const double _d = 1.0;
    double _degree;
};

#endif // SENSOR_H
