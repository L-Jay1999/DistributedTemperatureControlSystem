#include "usermanagementwidget.h"
#include "ui_usermanagementwidget.h"

UserManagementWidget::UserManagementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagementWidget)
{
    ui->setupUi(this);
    setWindowTitle("用户管理");
    setFixedSize(this->width(),this->height());
    connect(ui->pushButton_add,&QPushButton::clicked,this,&UserManagementWidget::Add);
    connect(ui->pushButton_delete,&QPushButton::clicked,this,&UserManagementWidget::Delete);
    connect(ui->pushButton_close,&QPushButton::clicked,this,&UserManagementWidget::Close);
    connect(ui->pushButton_clear,&QPushButton::clicked,this,&UserManagementWidget::Clear);
    ui->user_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

UserManagementWidget::~UserManagementWidget()
{
    delete ui;
}

void UserManagementWidget::Add()
{
    _RoomID = ui->lineEdit_roomid->text();
    _UserID = ui->lineEdit_userid->text();
    //调用UserInfoControl::AddUser()，并根据response设置提示信息
    _response = user_info.AddUser(_RoomID,_UserID);
    // _response = {true, "添加成功"};
    pd = new PromptDialog;
    pd->setText(std::get<1>(_response));
    pd->exec();
    Refresh();
}

void UserManagementWidget::Delete()
{
    _RoomID = ui->lineEdit_roomid->text();
    _UserID = ui->lineEdit_userid->text();
    //调用UserInfoControl::DeleteUser()，并根据response设置提示信息
    _response = user_info.DeleteUser(_RoomID,_UserID);
    // _response = {true, "删除失败"};
    pd = new PromptDialog;
    pd->setText(std::get<1>(_response));
    pd->exec();
    Refresh();
}

void UserManagementWidget::Refresh()
{
    //调用UserInfoControl::GetUserList()获得当前房客信息
    //_UserList = UserInfoControl::GetUserList();
    //_UserList
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
