#include "fileop.h"
#include "extramnk.h"
#include "mathmethods.h"
#include <QDebug>

QVector<float> FileOp::FLmass(data_size);

FileOp::RData FileOp::valRData;
int FileOp::NDataSize;

void FileOp::ReadFile(QString RFileName)
{
    QFile RFile(RFileName);
    if (!RFile.open(QFile::ReadOnly)) return;
    else
    {
        QTextStream RText(&RFile);
        QString RContent=RText.readAll();
        QStringList RList = RContent.split("\n");
        qDebug()<<RList.size();
        NDataSize=RList.size();
        for (int i=0;i<RList.size();i++)
        {
        QStringList Cols=RList.at(i).split("\t");
        valRData.InSignalVect.append(i);
        //valRData.InTimeVect.append(i);
        valRData.InSignalVect[i]=Cols.at(0).toFloat();
        //valRData.InTimeVect[i]=Cols.at(1).toFloat();
        }
        RFile.close();
    }

}

void FileOp::WriteFile(QString WFileName){


    QFile WFile(WFileName);
      if (!WFile.open(QFile::ReadOnly)){
        WFile.close();
        WFile.open(QFile::WriteOnly);
        QTextStream WText(&WFile);
        WText<<"\n";
        for (int i=0;i<data_size;i++)
        {
            WText<<"\n";
                         ;
            //WText<<G_file::kData[i];

        }

    }
    else{
        QTextStream WText(&WFile);
        //QStringList idList;
        QString WContent=WText.readAll();
        QStringList WList = WContent.split("\n");
        //currentid = idList.size();
        WFile.close();
        WFile.open(QFile::Append| QFile::Text);
                 WText<<"\n";
                  for (int i=0;i<NDataSize;i++)
                  {
                      WText<<"\n";
                      //OutText<<MathMethods::valIDFTData.IAmpl[i];
                      //WText<<MathMethods::valIDFTData.IAmpl[i];
                      WText<<ExtraMNK::PolData[i];
                  }
    }
    WFile.close();

}
