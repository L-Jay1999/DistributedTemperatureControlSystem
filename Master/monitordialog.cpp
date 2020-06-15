#include "monitordialog.h"
#include "ui_monitordialog.h"

#include <mutex>
#include <set>

MonitorDialog::MonitorDialog(int interval_sec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorDialog), _rooms(getRooms()), _interval(interval_sec)
{
    ui->setupUi(this);
    connect(&_timer, &QTimer::timeout, this, &MonitorDialog::updateTable);
    updateTable();
    _timer.start(interval_sec * 1000);
}

MonitorDialog::~MonitorDialog()
{
    delete ui;
}
static std::mutex mtx;

void MonitorDialog::setUpdateInterval(int interval_sec)
{
    std::lock_guard lock(mtx);

    _timer.stop();
    updateTable();
    _interval = interval_sec;
    _timer.start(_interval * 1000);
}

void MonitorDialog::updateTable()
{
    DBAccess db;
    qDebug() << "MonitorDialog::updateTable() called!";
    auto [is_suc, users] = db.getUsers();
    std::set<QString> all_rooms;
    if (!is_suc)
    {
        qDebug() << "MonitorDialog::updateTable(): failed to get users.";
        return;
    }

    for (const auto user : users)
    {
        const auto &room_id = std::get<0>(user);
        all_rooms.insert(room_id);
    }
    ui->monitor_tablewidget->clearContents();
    ui->monitor_tablewidget->setRowCount(all_rooms.size());

    int i = 0;
    for (const auto &room_id : all_rooms)
    {
        QTableWidgetItem *room_id_item, *is_open_item, *room_temp_item,
                *target_temp_item, *wind_speed_item, *has_wind_item;
        room_id_item = new QTableWidgetItem;
        is_open_item = new QTableWidgetItem;
        room_temp_item = new QTableWidgetItem;
        target_temp_item = new QTableWidgetItem;
        wind_speed_item = new QTableWidgetItem;
        has_wind_item = new QTableWidgetItem;

        room_id_item->setTextAlignment(Qt::AlignCenter);
        is_open_item->setTextAlignment(Qt::AlignCenter);
        room_temp_item->setTextAlignment(Qt::AlignCenter);
        target_temp_item->setTextAlignment(Qt::AlignCenter);
        wind_speed_item->setTextAlignment(Qt::AlignCenter);
        has_wind_item->setTextAlignment(Qt::AlignCenter);

        room_id_item->setText(room_id);
        if (_rooms.hasRoom(room_id))
        {
            is_open_item->setText("已开机");
            auto room_info = _rooms.getRoom(room_id);
            room_temp_item->setText(QString::number(room_info.config.getCurTemperature()));
            target_temp_item->setText(QString::number(room_info.config.getTemperature()));
            if (room_info.has_wind)
            {
                has_wind_item->setText("送风中");
                switch (room_info.config.getLevel())
                {
                case SpeedLevel::LOW:
                    wind_speed_item->setText("低");
                    break;
                case SpeedLevel::MID:
                    wind_speed_item->setText("中");
                    break;
                case SpeedLevel::HIGH:
                    wind_speed_item->setText("高");
                    break;
                default:
                    break;
                }
            }
            else
            {
                has_wind_item->setText("不送风");
                wind_speed_item->setText("无");
            }
        }
        else
        {
            is_open_item->setText("未开机");
            room_temp_item->setText("未知");
            target_temp_item->setText("未知");
            wind_speed_item->setText("未知");
            has_wind_item->setText("未知");
        }

        ui->monitor_tablewidget->setItem(i, 0, room_id_item);
        ui->monitor_tablewidget->setItem(i, 1, is_open_item);
        ui->monitor_tablewidget->setItem(i, 2, room_temp_item);
        ui->monitor_tablewidget->setItem(i, 3, target_temp_item);
        ui->monitor_tablewidget->setItem(i, 4, wind_speed_item);
        ui->monitor_tablewidget->setItem(i, 5, has_wind_item);
        i++;
    }
}


