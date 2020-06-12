#ifndef SLAVECONTROLWINDOW_H
#define SLAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QTimer>
#include <QLabel>

#include "user.h"
#include "sensor.h"
#include "shutdowncontroller.h"
#include "setspeedcontroller.h"
#include "settemperaturecontroller.h"
#include "useandcostcontroller.h"
#include "windcontroller.h"
#include "modealtercontroller.h"
#include "../CommonLib/common.h"

namespace Ui {
class SlaveControlWindow;
}

class SlaveControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlaveControlWindow(QWidget *parent = 0);
    ~SlaveControlWindow();

    void setUser(User *value);

private slots:
    void on_windspeedbtn_clicked();

    void on_shutdownbtn_clicked();

    void on_uptemperaturebtn_clicked();

    void on_downtemperaturebtn_clicked();


public slots:
    void GetUseandCost();
    void GetRoomTemperature();
    void GetMode(WorkingMode mode);
    void reachTargetDegree();

private:
    Ui::SlaveControlWindow *ui;
    User *_user;
    Sensor *_sensor;
//    QTimer *_timer;
    UseAndCostController *_useandcostcontroller;
    ModeAlterController *_modealtercontroller;

    QLCDNumber *_temperature_lcd;
    QLCDNumber *_windspeed_lcd;
    QLCDNumber *_roomtemperature_lcd;
    QLCDNumber *_usage_lcd;
    QLCDNumber *_cost_lcd;
    QLabel *_mode_text;
    QLabel *_wind_text;

    double _temperature;
    int _windspeed;
    double _roomtemperature;
    double _usage;
    double _cost;
    WorkingMode _mode;
    bool _is_open;
    bool _is_wind;

    double _upperbound;
    double _lowerbound;
//    const int _interval[3] = {25000, 20000, 15000};

    int WindSpeed(SpeedLevel speedlevel);
    SpeedLevel WindSpeed(int speedlevel);
    void ModeDisplay();
    void WindDisplay();
    void UpdateBound();
//    void SetInterval();

};

#endif // SLAVECONTROLWINDOW_H
