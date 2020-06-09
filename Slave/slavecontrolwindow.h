#ifndef SLAVECONTROLWINDOW_H
#define SLAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>

#include <../CommonLib/common.h>

namespace Ui {
class SlaveControlWindow;
}

class SlaveControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlaveControlWindow(QWidget *parent = 0);
    ~SlaveControlWindow();

private:
    Ui::SlaveControlWindow *ui;
    QLCDNumber *_temperature_lcd;
    QLCDNumber *_windspeed_lcd;
    QLCDNumber *_roomtemperature_lcd;
    QLCDNumber *_usage_lcd;
    QLCDNumber *_cost_lcd;
    double _temperature;
    int _windspeed;
    double _roomtemperature;
    double _usage;
    double _cost;

    int WindSpeed(SpeedLevel speedlevel);
    SpeedLevel WindSpeed(int speedlevel);
    void Temperature_Up();
    void Temperature_Down();
    void WindSpeed_Up();
    void WindSpeed_Down();
};

#endif // SLAVECONTROLWINDOW_H
