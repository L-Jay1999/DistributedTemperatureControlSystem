#ifndef SLAVECONTROLWINDOW_H
#define SLAVECONTROLWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>

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
};

#endif // SLAVECONTROLWINDOW_H
