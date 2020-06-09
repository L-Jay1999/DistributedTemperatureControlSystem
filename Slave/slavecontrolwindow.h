#ifndef SLAVECONTROLWINDOW_H
#define SLAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>

#include "user.h"
#include "shutdowncontroller.h"
#include "setspeedcontroller.h"
#include "settemperaturecontroller.h"
#include "useandcostcontroller.h"
#include "windcontroller.h"
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

private:
    Ui::SlaveControlWindow *ui;
    User *_user;
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
};

#endif // SLAVECONTROLWINDOW_H
