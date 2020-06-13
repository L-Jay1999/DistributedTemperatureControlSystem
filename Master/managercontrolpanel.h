#ifndef MANAGERCONTROLPANEL_H
#define MANAGERCONTROLPANEL_H

#include <QWidget>
#include "powersupplywidget.h"
#include "parameterwidget.h"
#include "monitorwidget.h"

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
    PowerSupplyWidget *psw;//电源开关面板
    ParameterWidget *pw;//参数设置面板
    MonitorWidget *mw;
    QString power;
    QString mode;
private slots:
    void logout();//登出
    void reshow_power();//回显
    void reshow_mode();
    void switch_to_power();//切换到电源控制
    void switch_to_parameter();//切换到参数设置
    void switch_to_log();//切换到日志
    void switch_to_monitor();//切换到监控
signals:
    void logout_signal();
};

#endif // MANAGERCONTROLPANEL_H
