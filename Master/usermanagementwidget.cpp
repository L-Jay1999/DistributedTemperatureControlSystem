#include "usermanagementwidget.h"
#include "ui_usermanagementwidget.h"

#include <QMessageBox>

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
    Refresh();
}

UserManagementWidget::~UserManagementWidget()
{
    delete ui;
}

void UserManagementWidget::Add()
{
    _RoomID = ui->lineEdit_roomid->text();
    _UserID = ui->lineEdit_userid->text();
    if (!CheckArgs())
    {
        QMessageBox::warning(this, "用户添加", "身份证格式不正确", QMessageBox::Ok);
    }
    else
    {
        auto [is_suc, response] = user_info.AddUser(_RoomID,_UserID);
        QMessageBox::information(this, "用户添加", response, QMessageBox::Ok);
        Refresh();
    }
}

void UserManagementWidget::Delete()
{
    _RoomID = ui->lineEdit_roomid->text();
    _UserID = ui->lineEdit_userid->text();
    if (!CheckArgs())
    {
        QMessageBox::warning(this, "用户添加", "身份证格式不正确", QMessageBox::Ok);
    }
    else
    {
        auto [is_suc, response] = user_info.DeleteUser(_RoomID,_UserID);
        QMessageBox::information(this, "用户删除", response, QMessageBox::Ok);
        Refresh();
    }
}

void UserManagementWidget::Refresh()
{
    ui->user_table->clearContents();
    auto [is_suc, rooms_and_ids] = user_info.GetUser();
    ui->user_table->setRowCount(rooms_and_ids.size());
    int i = 0;
    for (const auto [room_id, user_id] : rooms_and_ids)
    {
        QTableWidgetItem *room_id_item, *user_id_item;
        room_id_item = new QTableWidgetItem;
        user_id_item = new QTableWidgetItem;

        room_id_item->setText(room_id);
        room_id_item->setTextAlignment(Qt::AlignCenter);
        user_id_item->setText(user_id);
        user_id_item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        ui->user_table->setItem(i, 0, room_id_item);
        ui->user_table->setItem(i, 1, user_id_item);
        i++;
    }
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

bool UserManagementWidget::CheckArgs()
{
#ifdef ENABLE_ARG_CHECK
    QRegExp re("[0-9]{17}[0-9xX]");
    return re.exactMatch(_UserID) && _RoomID.length();
#else
    return true;
#endif
}
