#include "mainpredict.h"
#include <QApplication>
#include "mathmethods.h"
#include "QDebug"
#include "fileop.h"
#include <QElapsedTimer>
float Sig[10]={1,2,3,4,5,6,7,8,9,10};
float Out[10];

//void FileOp::Mass()
//{
//   // RD.FLoat.resize(100);
//    for (int i=0;i<=90;i++)
//    {
//        valRData.InSignalVect.append(i);
//    }
//}

QElapsedTimer timer;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainPredict w;
    w.show();
   // qDebug() << MainPredict::flag_computing;
   // FileOp::ReadFile("/home/lena/newQtpro/data_pred3.txt");

//     FileOp::ReadFile(FileOp::existFileName);
//    float INData[FileOp::NDataSize];
//    float INBuff[100];
//    for (int i=0;i<FileOp::NDataSize;i++) {
//        INData[i]=FileOp::valRData.InSignalVect.at(i);
//         qDebug() << FileOp::valRData.InSignalVect.at(i);
//    }
//    timer.start();
//     MathMethods::DFT(INData,NLengthBuff);
//     MathMethods::IDFT(MathMethods::valDFTData.ReSpec,MathMethods::valDFTData.ImSpec,FileOp::NDataSize,NLengthBuff);
//     for (int i=0;i<FileOp::NDataSize;i++) qDebug()<<MathMethods::valIDFTData.IAmpl[i]<<"     "<<i;

    return a.exec();
}
