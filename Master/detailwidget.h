#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include "report.h"
#include <string>
#include <fstream>
#include <sstream>
#include <QMessageBox>

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWidget(QWidget *parent = 0);
    ~DetailWidget();

private:
    Ui::DetailWidget *ui;
    Report _report;
    QDateTime _begin;
    QDateTime _end;
private slots:
    void GetDetails();//点击查询
    void DownLoad();//点击打印报表
    void Cancel();//返回
signals:
};

#endif // DETAILWIDGET_H
