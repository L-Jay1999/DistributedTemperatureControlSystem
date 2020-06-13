#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent)
{
    createView();
}

void MonitorWidget::createView()
{
    mainLayout = new QVBoxLayout;
        mainLayout->setSpacing(10);
        mainLayout->setMargin(10);
//        testBtn = new QPushButton("Test");
//        m_PushButton = new QPushButton("PushButton");

        tableView = new QTableView;
        standItemModel = new QStandardItemModel();

        standItemModel->setColumnCount(5);
        standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("房间号"));
        standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("开关状态"));
        standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("当前温度"));
        standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("送风状态"));
        standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("当前风速"));

        //向表格添加100行内容
        for(int i=0;i<100;i++)
        {
            QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(i+1));
            QStandardItem *standItem2 = new QStandardItem((QString)tr("line %1").arg(i+1));
            standItemModel->setItem(i,0,standItem1);
            standItemModel->item(i,0)->setForeground(QBrush(QColor(255,0,0)));
            standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);
//            standItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);
            standItemModel->setItem(i,1,standItem2);
            standItemModel->setItem(i,2,standItem2);

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
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //需要在表格使用右键菜单，需要启动该属性
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //表格第0列，按降序排列

//        tableView->setIndexWidget(standItemModel->index(10,1),m_PushButton);
//        tableView->setIndexWidget(standItemModel->index(10,2),testBtn);
        tableView->setShowGrid(false);

//        standItemModel->removeRows(0,10);

    //    mainLayout->addWidget(testBtn);
        mainLayout->addWidget(tableView);
        this->setLayout(mainLayout);
}

