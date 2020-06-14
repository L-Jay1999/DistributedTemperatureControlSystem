#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::GetReport()
{

}
