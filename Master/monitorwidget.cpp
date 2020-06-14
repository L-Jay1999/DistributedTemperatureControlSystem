#include "monitorwidget.h"
#include "report.h"

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


        auto room_ids = getRooms().getRoomIDs();
        int i = 0;
        for(auto &room_id : room_ids)
        {
            QString realid = getRooms().getRoom(room_id).room_id;
            QString is_open, has_wind, mode, level;
            if(getRooms().getRoom(room_id).is_open == true)
            {
                 is_open = "OPEN";
            }else{
                is_open = "CLOSE";
            }
            if(getRooms().getRoom(room_id).has_wind == true)
            {
                 is_open = "WINDING";
            }else{
                is_open = "STOP";
            }
            if(getRooms().getRoom(room_id).config.getMode() == WorkingMode(0))
            {
                mode = "COLD";
            }else if(getRooms().getRoom(room_id).config.getMode() == WorkingMode(1)){
                mode = "HOT";
            }
            if(getRooms().getRoom(room_id).config.getLevel() == SpeedLevel(0))
            {
                level = "LOW";
            }else if(getRooms().getRoom(room_id).config.getLevel() == SpeedLevel(1)){
                level = "MID";
            }else{
                level = "HIGH";
            }
            double working_degree = getRooms().getRoom(room_id).config.getTemperature();
            double current_degree = getRooms().getRoom(room_id).config.getCurTemperature();
            QStandardItem *standItem1 = new QStandardItem(tr(realid.toLocal8Bit().data()).arg(i+1));//房间号
            QStandardItem *standItem2 = new QStandardItem(tr(is_open.toLocal8Bit().data()).arg(i+1));
            QStandardItem *standItem3 = new QStandardItem(tr(QByteArray::number(current_degree).data()).arg(i+1));
            QStandardItem *standItem4 = new QStandardItem(tr(has_wind.toLocal8Bit().data()).arg(i+1));
            QStandardItem *standItem5 = new QStandardItem(tr(level.toLocal8Bit().data()).arg(i+1));
            standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));
            standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);
            standItemModel->setItem(i,0,standItem1);
            standItemModel->setItem(i,1,standItem2);
            standItemModel->setItem(i,2,standItem3);
            standItemModel->setItem(i,4,standItem4);
            standItemModel->setItem(i,5,standItem5);
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

