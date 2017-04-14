#include "mainpredict.h"
#include "ui_mainpredict.h"
#include <QDebug>
#include "fileop.h"
#include "mathmethods.h"
#include "extramnk.h"
#include <QtGui>

QString FileOp::existFileNameOpen;
QString FileOp::existFileNameWrite;
int MainPredict::flag_computing;
MainPredict::MainPredict(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPredict)
{
    ui->setupUi(this);
}

MainPredict::~MainPredict()
{
    delete ui;
}
void MainPredict::on_action_Write_triggered()
{
//    DWriteFile1 = new DWriteFile;
//    connect(DWriteFile1,SIGNAL(DWriteFileSend(QString)),this,SLOT(DWriteFileReceive(QString)));
//    DWriteFile1->show();
    FileOp::existFileNameWrite=QFileDialog::getOpenFileName(this,QString::fromUtf8("Open File"),QDir::currentPath(),"All files(*.*)");
}

void MainPredict::on_action_Open_triggered()
{
//   FileDialog1 = new FileDialog;
//   connect(FileDialog1,SIGNAL(FileOpenSend(QString)),this,SLOT(FileOpenReceive(QString)));
//   FileDialog1->show();
    FileOp::existFileNameOpen=QFileDialog::getOpenFileName(this,QString::fromUtf8("Open File"),QDir::currentPath(),"All files(*.*)");

}

 void MainPredict::FileOpenReceive(QString filename){
   qDebug() << filename;
   FileOp::existFileNameOpen=filename;
 }

 void MainPredict::DWriteFileReceive(QString filename)
 {
     qDebug() << filename;
     FileOp::existFileNameWrite=filename;
 }

void MainPredict::on_pushButton_clicked()
{
  //MathMethods::MainComputing();
    ExtraMNK::MainComputing();
}

void MainPredict::on_actionParams_triggered()
{
  Params_mat1 = new Params_mat;
  Params_mat1->show();
}
