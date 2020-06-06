#include "slavecontrolwindow.h"
#include "ui_slavecontrolwindow.h"

SlaveControlWindow::SlaveControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlaveControlWindow)
{
    ui->setupUi(this);
    _temperature_lcd = ui->_temperature_lcd;
    _roomtemperature_lcd = ui->_roomtemperature_lcd;
    _cost_lcd = ui->_cost_lcd;
    _windspeed_lcd = ui->_windspeed_lcd;
    _usage_lcd = ui->_usage_lcd;

    _temperature_lcd->display(36.2);
}

SlaveControlWindow::~SlaveControlWindow()
{
    delete ui;
    exit(0);
}
