#include "monitordialog.h"
#include "ui_monitordialog.h"

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
