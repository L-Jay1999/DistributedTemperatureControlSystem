#include "sensor.h"

#include <QObject>

#include <map>
#include <mutex>

const std::map<SpeedLevel, double> Sensor::kTempChangePerSecWind =
{
    {SpeedLevel::LOW, 1.0 / 25.0},
    {SpeedLevel::MID, 1.0 / 20.0},
    {SpeedLevel::HIGH, 1.0 / 15.0},
};

static std::mutex sensor_set_mtx;
static std::mutex sensor_update_mtx;
static constexpr double epsilon = 1e-3;


Sensor::Sensor(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(reachTargetDegree()), parent, SLOT(reachTargetDegree()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(TimerUp()));
    _last_update_time = QDateTime::currentMSecsSinceEpoch();
    _timer.start(kDefaultTimerInterval);
}

double Sensor::GetTemperature()
{
    return _current_degree;
}

void Sensor::setTargetDegree(double target_degree)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _target_degree = target_degree;
    StartTimer();
}

void Sensor::setWindSpeed(SpeedLevel windspeed)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _speed = windspeed;
    StartTimer();
}

void Sensor::setIsWind(bool is_wind)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _is_wind = is_wind;
    StartTimer();
}

void Sensor::setWorkingMode(WorkingMode mode)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _mode = mode;
    StartTimer();
}

void Sensor::StartTimer()
{
    if (_is_wind)
    {
        double diff = std::fabs(_current_degree - _target_degree);

        if (diff < kTempChangePerSecWind.at(_speed))
            _timer.start(diff / kTempChangePerSecWind.at(_speed) * 1000.0);
        else
            _timer.start(kDefaultTimerInterval);
    }
    else
    {
        double diff = std::fabs(_current_degree - _room_init_degree);

        if (diff < kTempChangePerSecRoom)
            _timer.start(diff / kTempChangePerSecRoom * 1000.0);
        else
            _timer.start(kDefaultTimerInterval);
    }
}

void Sensor::UpdateTemperature()
{
    std::lock_guard lock(sensor_update_mtx);
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    double diff_sec = (now - _last_update_time) / 1000.0;
    double degree_diff;
    if (_is_wind)
    {
        degree_diff = kTempChangePerSecWind.at(_speed) * diff_sec;
        if (_mode == WorkingMode::COLD)
        {
            _current_degree -= degree_diff;
            if (_current_degree <= _target_degree + epsilon)
            {
                emit reachTargetDegree();
                _current_degree = _target_degree;
            }
        }
        else
        {
            _current_degree += degree_diff;
            if (_current_degree >= _target_degree - epsilon)
            {
                emit reachTargetDegree();
                _current_degree = _target_degree;
            }
        }
    }
    else
    {
        degree_diff = kTempChangePerSecRoom * diff_sec;
        if (std::abs(_room_init_degree - _current_degree) > epsilon)
        {
            if (_current_degree < _room_init_degree)
                _current_degree += degree_diff;
            else
                _current_degree -= degree_diff;
        }
    }
}

void Sensor::TimerUp()
{
    _timer.stop();
    UpdateTemperature();
    StartTimer();
}
