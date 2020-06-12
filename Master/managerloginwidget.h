#ifndef MANAGERLOGINWIDGET_H
#define MANAGERLOGINWIDGET_H

#include <QWidget>
#include "managercontrolpanel.h"
#include "managerlogincontroller.h"
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
    ManagerLoginController *mlc;
    std::tuple<bool,QString> login_res;//认证回复与错误提示信息
private slots:
    void confirm();//点击确认
    void cancel();//点击退出
signals:
    void cancel_signal();//退出信号
    void certified_signal();//通过认证信号
};

#endif // MANAGERLOGINWIDGET_H
