#include "usermanagementwidget.h"
#include "ui_usermanagementwidget.h"

UserManagementWidget::UserManagementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagementWidget)
{
    ui->setupUi(this);
    setWindowTitle("用户管理");
    ui->textEdit->setReadOnly(true);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit->setCalendarPopup(true);
    connect(ui->pushButton_add,&QPushButton::clicked,this,&UserManagementWidget::Add);
    connect(ui->pushButton_delete,&QPushButton::clicked,this,&UserManagementWidget::Delete);
    connect(ui->pushButton_refresh,&QPushButton::clicked,this,&UserManagementWidget::Refresh);
    connect(ui->pushButton_close,&QPushButton::clicked,this,&UserManagementWidget::Close);
    connect(ui->pushButton_clear,&QPushButton::clicked,this,&UserManagementWidget::Clear);

}

UserManagementWidget::~UserManagementWidget()
{
    delete ui;
}

void UserManagementWidget::Add()
{
    _RoomID = ui->lineEdit_roomid->text();
    _UserID = ui->lineEdit_userid->text();
    _EffDateTime = ui->dateTimeEdit->dateTime();
    _CurDateTime = QDateTime::currentDateTime();
    int tRet = _EffDateTime.toTime_t() - _CurDateTime.toTime_t();
    if(tRet > 0)
    {
        //调用UserInfoControl::AddUser()，并根据response设置提示信息，若成功，则调用一次Refresh
        _PromptText = "添加成功";
    }else
    {
        _PromptText = "添加失败：非法的有效日期";
    }
    pd = new PromptDialog;
    pd->setText(_PromptText);
    pd->exec();
}

void UserManagementWidget::Delete()
{

}

void UserManagementWidget::Refresh()
{

}

void UserManagementWidget::Clear()
{
    ui->lineEdit_roomid->clear();
    ui->lineEdit_userid->clear();
}

void UserManagementWidget::Close()
{
    emit cancel_signal();
    this->hide();
}
