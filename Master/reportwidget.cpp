#include "reportwidget.h"
#include "ui_reportwidget.h"

ReportWidget::ReportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit_cost->setReadOnly(true);
    ui->lineEdit_power->setReadOnly(true);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setCalendarPopup(true);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"起始时间"<<"终止时间"<<"起始温度"<<"终止温度"<<"风量消耗"<<"单次费用");
    connect(ui->pushButton_confirm,&QPushButton::clicked,this,&ReportWidget::GetReport);
    connect(ui->pushButton_download,&QPushButton::clicked,this,&ReportWidget::DownLoad);
    connect(ui->pushButton_cancel,&QPushButton::clicked,this,&ReportWidget::Cancel);
}

ReportWidget::~ReportWidget()
{
    delete ui;
}

void ReportWidget::GetReport()
{
    _roomid = ui->lineEdit_roomid->text();
    _date = ui->dateEdit->date();
    if(_report.getDateReport(_date) == true)
    {
        std::vector<StatPayload> rep = _report.getRoomReport(_roomid);
        ui->tableWidget->setRowCount(rep.size());
        for(int i = 0; i < rep.size(); i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(rep[i].start_time.toString("yyyy-MM-dd hh:mm:ss")));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(rep[i].end_time.toString("yyyy-MM-dd hh:mm:ss")));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(rep[i].init_temperature)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(rep[i].end_temperature)));
            //TODO 计算风量消耗
            //ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number()));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(rep[i].cost)));
        }
    }
    ui->lineEdit_power->setText(QString::number(_report.getPowerSupply(_roomid)));
    ui->lineEdit_cost->setText(QString::number(_report.getCost(_roomid)));
}

void ReportWidget::DownLoad()
{
    GetReport();
    using namespace std;
    string path = "./report/" + _date.toString("yyyy-MM-dd").toStdString() + '_' + _roomid.toStdString() + ".csv";
    ofstream outf;
    outf.open(path,ios::out);
    outf << "Date" << ',' << "RoomID" << ',' << "Power Supply" << ',' << "Total Cost" << endl;
    outf << _date.toString("yyyy-MM-dd").toStdString() << ','
         << _roomid.toStdString() << ','
         << ui->lineEdit_power->text().toStdString() << ','
         << ui->lineEdit_cost->text().toStdString() << endl;
    outf << "Start Time" << ',' << "End Time" << ',' << "Init Temperature" << ',' << "End Temperature" << ',' << "Air Volume" << ',' << "Cost" << endl;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        outf << ui->tableWidget->item(i,0)->text().toStdString() << ','
             << ui->tableWidget->item(i,1)->text().toStdString() << ','
             << ui->tableWidget->item(i,2)->text().toStdString() << ','
             << ui->tableWidget->item(i,3)->text().toStdString() << ','
             << ui->tableWidget->item(i,4)->text().toStdString() << ','
             << ui->tableWidget->item(i,5)->text().toStdString() << endl;
    }
    outf.close();
}

void ReportWidget::Cancel()
{
    emit cancel_signal();
    this->hide();
}
