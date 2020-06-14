#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include "report.h"

namespace Ui {
class ReportWidget;
}

class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = 0);
    ~ReportWidget();

private:
    Ui::ReportWidget *ui;
    Report _report;
private slots:
    void GetReport();//点击查询
signals:
    void cancel_signal();
};

#endif // REPORTWIDGET_H
