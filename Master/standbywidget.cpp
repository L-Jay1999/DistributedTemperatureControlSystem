#include "standbywidget.h"
#include "ui_standbywidget.h"

StandbyWidget::StandbyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandbyWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("中央空调控制系统-待机");
    this->setFixedSize(this->width(),this->height());
    ui->label_mode->setText(QStringLiteral("无"));
    connect(ui->btn_login, &QPushButton::clicked, this, &StandbyWidget::switch_to_login);//点击认证按钮
}

StandbyWidget::~StandbyWidget()
{
    delete ui;
}

void StandbyWidget::reshow()
{
    this->show();
}

void StandbyWidget::switch_to_login()//切换到管理员认证窗口
{
    mlw = new ManagerLoginWidget;
    mlw->show();
    connect(mlw,SIGNAL(cancel_signal()),this,SLOT(reshow()));//连接取消信号与回显
    connect(mlw,SIGNAL(certified_signal(const QString &)),this,SLOT(switch_to_panel(const QString &)));//收到信号表示认证成功，切换到控制面板
    this->hide();
}

void StandbyWidget::switch_to_panel(const QString &manager_account)//切换到中央空调控制面板
{
    mcp = new ManagerControlPanel(manager_account);
    mcp->show();
    connect(mcp,SIGNAL(logout_signal()),this,SLOT(reshow()));//连接登出信号与回显
    this->hide();
}
