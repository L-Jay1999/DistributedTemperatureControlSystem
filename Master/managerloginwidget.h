#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H

#include <QWidget>
#include "managerlogincontroller.h"
#include "managercontrolpanel.h"

namespace Ui {
class ManagerLoginWidget;
}

class ManagerLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerLoginWidget(QWidget *parent = 0);
    ~ManagerLoginWidget();
private:
    Ui::ManagerLoginWidget *ui;
    ManagerControlPanel *mcp;
    std::tuple<bool,QString> Login();//进行认证
private slots:
    void confirm();//点击确认
    void cancel();//点击退出
signals:
    void cancel_signal();//退出信号
    void certified_signal(const QString &manager_account);//通过认证信号
};

#endif // MANAGERLOGINWIDGET_H
