#ifndef SLAVECONTROLWINDOW_H
#define SLAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QTimer>
#include <QLabel>
#include <memory>

#include "user.h"
#include "sensor.h"
#include "shutdowncontroller.h"
#include "setspeedcontroller.h"
#include "settemperaturecontroller.h"
#include "useandcostcontroller.h"
#include "windcontroller.h"
#include "modealtercontroller.h"
#include "userlogindialog.h"
#include "gettemperaturecontroller.h"
#include "common.h"

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
    void higherThanTargetDegreePlusOne();
    void SetLoginUser(const QString &room_id, const QString &_id, WorkingMode mode, double init_temp);

private:
    Ui::SlaveControlWindow *ui;
    User *_user;
    Sensor *_sensor;
    QTimer *_timer;
    UseAndCostController *_useandcostcontroller;
    ModeAlterController *_modealtercontroller;
    GetTemperatureController *_gettemperaturecontroller;

    QLCDNumber *_temperature_lcd;
    QLCDNumber *_windspeed_lcd;
    QLCDNumber *_roomtemperature_lcd;
    QLCDNumber *_usage_lcd;
    QLCDNumber *_cost_lcd;
    QLabel *_mode_text;
    QLabel *_wind_text;

    double _temperature{};
    int _windspeed{};
    double _roomtemperature{};
    double _usage{};
    double _cost{};
    WorkingMode _mode{};
    bool _is_open{false};
    bool _is_wind{false};

    double _upperbound = 25.0;
    double _lowerbound = 18.0;

    int WindSpeed(SpeedLevel speedlevel);
    SpeedLevel WindSpeed(int speedlevel);
    void ModeDisplay();
    void WindDisplay();
    void UpdateBound();
    void ShutDownDisplays();
    void ShutDown();
    bool SendWind();

};

#endif // SLAVECONTROLWINDOW_H
