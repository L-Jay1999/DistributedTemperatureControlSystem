﻿#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent)
{
    createView();
}

void MonitorWidget::createView()
{
    mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(10);
        mainLayout->setMargin(10);

        tableView = new QTableView(this);
        standItemModel = new QStandardItemModel(this);

        standItemModel->setColumnCount(5);
        standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("房间号"));
        standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("开关状态"));
        standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("当前温度"));
        standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("送风状态"));
        standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("当前风速"));

        //从DBAccess中拿到所有房间的数据
        QDateTime begin, end;
        begin.setDate(QDate::currentDate());
        end.setDate(QDate::currentDate().addDays(1));
        std::pair<bool, std::vector<StatPayload>> response = db.getRoomRequestStats(begin,end);//获取当日报表
        int i = 0;
        for(auto it = response.second.begin(); it != response.second.end();it ++)
        {
            const char *room_id =  it->room_id.toLocal8Bit().data();
            const char *room_temperature =  QByteArray::number(it->end_temperature).data();
            QString speed, power;
            if(it->speed_level == SpeedLevel::LOW)
            {
                speed = "low";
            }else if(it->speed_level == SpeedLevel::MID)
            {
                speed = "mid";
            }else{
                speed = "high";
            }
            const char *room_speedlevel = speed.toLocal8Bit().data();

            QDateTime current_date_time =QDateTime::currentDateTime();
            if(current_date_time > it->start_time && it->end_time < it->start_time)
            {
                power = "open";
            }else{
                power = "close";
            }
            const char *room_power= power.toLocal8Bit().data();

            QStandardItem *standItem1 = new QStandardItem(tr(room_id).arg(i+1));
            QStandardItem *standItem2 = new QStandardItem(tr(room_power).arg(i+1));
            QStandardItem *standItem3 = new QStandardItem(tr(room_temperature).arg(i+1));
            QStandardItem *standItem5 = new QStandardItem(tr(room_speedlevel).arg(i+1));
//            QStandardItem *standItem1 = new QStandardItem(tr(room_).arg(i+1));
            standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));
            standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);
            standItemModel->setItem(i,0,standItem1);
            standItemModel->setItem(i,1,standItem2);
            standItemModel->setItem(i,2,standItem3);
            standItemModel->setItem(i,4,standItem5);
            i++;
        }

        tableView->setModel(standItemModel);

        //设置表格属性
        tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
        tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);

        tableView->setColumnWidth(0,100);
        tableView->setColumnWidth(1,200);
        tableView->setColumnWidth(2, 200);
        tableView->setColumnWidth(3, 200);
        tableView->setColumnWidth(4, 200);

        tableView->verticalHeader()->hide();    //隐藏默认显示的行头
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setShowGrid(false);

        mainLayout->addWidget(tableView);
        this->setLayout(mainLayout);
}

