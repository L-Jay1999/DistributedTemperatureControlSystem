#include "promptdialog.h"
#include "ui_promptdialog.h"

PromptDialog::PromptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PromptDialog)
{
    ui->setupUi(this);
    setWindowTitle("提示");
    setAttribute(Qt::WA_DeleteOnClose);//关闭时销毁
    setModal(true);//设置为模态
}

PromptDialog::~PromptDialog()
{
    delete ui;
}

void PromptDialog::setText(QString text)
{
    ui->textEdit->setText(text);
    ui->textEdit->setReadOnly(true);//设置为只读
}
