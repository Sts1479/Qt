#include "dwritefile.h"
#include "ui_dwritefile.h"

DWriteFile::DWriteFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DWriteFile)
{
    ui->setupUi(this);
}

DWriteFile::~DWriteFile()
{
    delete ui;
}

void DWriteFile::on_pushButton_clicked()
{
    emit DWriteFileSend(ui->lineEdit->text());
    this->hide();
}
