#include "startupwindow.h"
#include "ui_startupwindow.h"

#include "userloginwidget.h"

StartUpWindow::StartUpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartUpWindow)
{
    ui->setupUi(this);
}

StartUpWindow::~StartUpWindow()
{
    delete ui;
}

void StartUpWindow::ShowUserLoginWidget()
{
    UserLoginWidget *user_login_widget = new UserLoginWidget();
    user_login_widget->show();
    close();
}
