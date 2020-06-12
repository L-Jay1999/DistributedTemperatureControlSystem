#include "sensor.h"

double Sensor::GetTemperature(double target)
{
    if(_degree == target)
        return _degree;
    else if(_degree > target){
        _degree -= _d;
        return _degree;
    }
    else{
        _degree += _d;
        return _degree;
    }
}
