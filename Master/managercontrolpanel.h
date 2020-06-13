#ifndef MANAGERCONTROLPANEL_H
#define MANAGERCONTROLPANEL_H

#include <QWidget>
#include "powersupplywidget.h"
#include "usermanagementwidget.h"

#include "../CommonLib/common.h"

namespace Ui {
class ManagerControlPanel;
}

class ManagerControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerControlPanel(const QString &manager_account, QWidget *parent = 0);
    ~ManagerControlPanel();

private:
    Ui::ManagerControlPanel *ui;
    QString _account;

    bool _has_power{false};
    int _rate{10};
    WorkingMode _mode{WorkingMode::COLD};

    PowerSupplyWidget *psw;//电源控制面板
    UserManagementWidget *umw;//用户管理面板

    void setPowerLabelText();
    void setModeLabelText();
    void setRateLabelText();

private slots:
    void logout();                  //登出
    void reshow();                  //回显
    void switch_to_power();         //切换到电源控制
    void switch_to_parameter();     //切换到参数设置
    void switch_to_log();           //切换到日志
    void switch_to_monitor();       //切换到监控
    void switch_to_user();          //切换到用户管理
    void set_power(bool has_power);
signals:
    void logout_signal();
};

#endif // MANAGERCONTROLPANEL_H
