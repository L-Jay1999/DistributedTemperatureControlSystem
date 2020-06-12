#include "operationconfirmationdialog.h"
#include "ui_operationconfirmationdialog.h"

OperationConfirmationDialog::OperationConfirmationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationConfirmationDialog)
{
    ui->setupUi(this);
    setWindowTitle("操作确认");
    setAttribute(Qt::WA_DeleteOnClose);
}

OperationConfirmationDialog::~OperationConfirmationDialog()
{
    delete ui;
}

void OperationConfirmationDialog::setText(QString text)
{
    text = "将执行操作:\n\n" + text + "\n\n是否确认？";
    ui->textEdit->setText(text);
}

