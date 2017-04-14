#include "filedialog.h"
#include "ui_filedialog.h"
//#include <QtGui>

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::on_pushButtonFile_clicked()
{
    //QString filename=QFileDialog::getOpenFileName(this,QString::fromUtf8("Open File"),QDir::currentPath(),"All files(*.*)");
    emit FileOpenSend(ui->lineEdit->text());
    this->hide();
}

