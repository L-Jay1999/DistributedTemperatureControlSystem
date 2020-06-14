#include "monitor_dialog.h"
#include "ui_monitor_dialog.h"

MonitorDialog::MonitorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorDialog)
{
    ui->setupUi(this);
}

MonitorDialog::~MonitorDialog()
{
    delete ui;
}
