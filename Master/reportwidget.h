#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include "report.h"
#include <string>
#include <fstream>
#include <sstream>
#include <QMessageBox>

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
    QString _roomid;
    QDate _date;
private slots:
    void GetReport();//点击查询
    void DownLoad();//点击打印报表
    void Cancel();//返回
signals:
    void cancel_signal();
};

#endif // REPORTWIDGET_H
