#ifndef MANAGERCONTROLPANEL_H
#define MANAGERCONTROLPANEL_H

#include <QWidget>
#include "powersupplywidget.h"
#include "usermanagementwidget.h"

namespace Ui {
class ManagerControlPanel;
}

class ManagerControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerControlPanel(QWidget *parent = 0);
    ~ManagerControlPanel();

private:
    Ui::ManagerControlPanel *ui;
    QString _mode, _account, _power, _rate;

    PowerSupplyWidget *psw;//电源控制面板
    UserManagementWidget *umw;//用户管理面板

private slots:
    void logout();                  //登出
    void reshow();                  //回显
    void switch_to_power();         //切换到电源控制
    void switch_to_parameter();     //切换到参数设置
    void switch_to_log();           //切换到日志
    void switch_to_monitor();       //切换到监控
    void switch_to_user();          //切换到用户管理
signals:
    void logout_signal();
};

#endif // MANAGERCONTROLPANEL_H
