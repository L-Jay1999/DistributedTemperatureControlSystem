#ifndef MANAGERCONTROLPANEL_H
#define MANAGERCONTROLPANEL_H

#include <QWidget>
#include "usermanagementwidget.h"
#include "reportwidget.h"
#include "monitordialog.h"
#include "../CommonLib/common.h"
#include "./listener.h"

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
    QThread *_thread;
    Listener *_listener;

    bool _has_power{false};
    int _rate{10};
    QTimer clear_error_info_timer;

    UserManagementWidget *umw;//用户管理面板
    MonitorDialog *monitor_dialog{nullptr};//监控信息界面
    ReportWidget *rw;//报表界面


    void setPowerLabelText();
    void setModeLabelText();
    void setRateLabelText();
    void setDefaultDegreeLabelText();
    void ChangeRate(bool is_rate_up);
    void ChangeDegree(bool is_degree_up);

private slots:
    void logout();                  //登出
    void reshow();                  //回显
    void switch_to_power();         //切换到电源控制
    void switch_to_detail();        //切换到详单查看
    void switch_to_report();        //切换到报表查看
    void show_monitor();       //切换到监控
    void switch_to_user();          //切换到用户管理
    void set_power_label_text(bool has_power);
    void change_mode();
    void set_error_info_text(const QString &err_info);
    void clear_error_info_text();

    void rate_up();
    void rate_down();
    void degree_up();
    void degree_down();
signals:
    void logout_signal();
    void SetErrorInfoTextSignal(const QString &err_info);
    void ClearErrorInfoTextSignal();
    void setMonitorInterval(int interval_sec);
    void StopListen();
    void StartListen();
};

#endif // MANAGERCONTROLPANEL_H
