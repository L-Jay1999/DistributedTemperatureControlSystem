#include "sensor.h"

Sensor::Sensor(QObject *parent) : QObject(parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(_interval[3]);
    _timer->start();

    _elapsedtimer = new QElapsedTimer();
    _elapsedtimer->start();
//    connect(_timer, SIGNAL(timeout()), this, SLOT(SendTemperature()));
}

double Sensor::GetTemperature()
{
    return _degree;
}

void Sensor::setTargetDegree(double target_degree)
{
    _target_degree = target_degree;
}

void Sensor::setWindSpeed(int windspeed)
{

//    _timer->setInterval(_interval[windspeed-1]);
//    _timer->start();
    _timer->stop();
    if(UpdateTemperature())
        _elapsedtimer->restart();
    _windspeed = windspeed;
    _timer->start(_interval[windspeed-1]);
}

void Sensor::setIsWind(bool is_wind)
{

    _timer->stop();
    if(UpdateTemperature())
        _elapsedtimer->restart();
    _is_wind = is_wind;
    if(!is_wind){
        _timer->start(_interval[3]);
    }
    else{
        _timer->start(_interval[_windspeed-1]);
    }
}

bool Sensor::UpdateTemperature()
{
    // todo
    int res = _elapsedtimer->elapsed()/_timer->interval();
    if(_is_wind){
        if(_degree == _target_degree){
            _timer->stop();
            return false;
        }
        else if(_degree < _target_degree){
            _degree += _d;
        }
        else{
            _degree -= _d;
        }
    }
    else{
        if(res){
            _degree += _d * res;
            return true;
        }
        return false;
    }
}
