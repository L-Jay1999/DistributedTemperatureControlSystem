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

static constexpr double epsilon = 1e-3;


Sensor::Sensor(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(reachTargetDegree()), parent, SLOT(reachTargetDegree()));
    connect(this, SIGNAL(higherThanTargetDegreePlusOne()), parent, SLOT(higherThanTargetDegreePlusOne()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(TimerUp()));
    _last_update_time = QDateTime::currentMSecsSinceEpoch();
    _timer.setSingleShot(true);
    _timer.start(kDefaultTimerInterval);
}

double Sensor::GetTemperature()
{
    return _current_degree;
}

void Sensor::setIsWindWithoutUpdate(bool is_wind)
{
    _is_wind = is_wind;
}

void Sensor::setTargetDegreeWithoutUpdate(double target_degree)
{
    _target_degree = target_degree;
}

void Sensor::setTargetDegree(double target_degree)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _target_degree = target_degree;
    StartTimer();
    qDebug() << "setTargetDegree(): " << target_degree;
}

void Sensor::setWindSpeed(SpeedLevel windspeed)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _speed = windspeed;
    StartTimer();
    qDebug() << "setWindSpeed(): " << EnumToInt(windspeed);
}

void Sensor::setIsWind(bool is_wind)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _is_wind = is_wind;
    StartTimer();
    qDebug() << "setIsWind(): " << is_wind;
}

void Sensor::setWorkingMode(WorkingMode mode)
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    _mode = mode;
    StartTimer();
    qDebug() << "setWorkingMode(): " << EnumToInt(mode);
}

void Sensor::StartTimer()
{
    if (_is_wind)
    {
        double diff = std::fabs(_current_degree - _target_degree);

        if (diff < epsilon)
            _timer.start(kDefaultTimerInterval);
        else if (diff < kTempChangePerSecWind.at(_speed))
            _timer.start(diff / kTempChangePerSecWind.at(_speed) * 1000.0);
        else
            _timer.start(kDefaultTimerInterval);
    }
    else
    {
        double diff = std::fabs(_current_degree - _room_init_degree);
        if (diff < epsilon)
            _timer.start(kDefaultTimerInterval);
        else if (diff < kTempChangePerSecRoom)
            _timer.start(diff / kTempChangePerSecRoom * 1000.0);
        else
            _timer.start(kDefaultTimerInterval);
    }
}

void Sensor::UpdateTemperature()
{
    std::lock_guard lock(sensor_update_mtx);
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    double diff_sec = (now - _last_update_time) / 300.0;
    double degree_diff;
    if (_is_wind)
    {
        degree_diff = kTempChangePerSecWind.at(_speed) * diff_sec;
        qDebug() << "diff for " << degree_diff;
        if (_mode == WorkingMode::COLD)
        {
            _current_degree -= degree_diff;
            if (_current_degree <= _target_degree + epsilon)
            {
                emit reachTargetDegree();
                _is_wind = false;
            }
        }
        else
        {
            _current_degree += degree_diff;
            if (_current_degree >= _target_degree - epsilon)
            {
                emit reachTargetDegree();
                _is_wind = false;
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
            if (_mode == WorkingMode::HOT && _current_degree < _target_degree - 1.0)
                emit higherThanTargetDegreePlusOne();
            else if (_mode == WorkingMode::COLD && _current_degree > _target_degree + 1.0)
                emit higherThanTargetDegreePlusOne();
        }
    }
    qDebug() << "current_degree: " << _current_degree << ", _last: " << _last_update_time << ", now: " << now;
    _last_update_time = now;
}

void Sensor::TimerUp()
{
    std::lock_guard lock(sensor_set_mtx);
    _timer.stop();
    UpdateTemperature();
    StartTimer();
    qDebug() << "TimerUp";
}
