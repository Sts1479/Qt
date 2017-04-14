#ifndef FILEOP_H
#define FILEOP_H
#include "qfile.h"
#include "qtextstream.h"
#include "qvector.h"
#define data_size 100
class FileOp //class for the operations with files
{
private:

public:
    static void ReadFile(QString RFileName);
    static void WriteFile(QString WFileName);
    static void Mass();
    static QVector<float> FLmass;
    static struct RData
    {
       QVector<float> InSignalVect;
       QVector<float> InTimeVect;
       //RData(){FLoat=QVector<float> (100);}
    }valRData;
    //static QVector<RData> MyData;
    static int NDataSize;
    static QString existFileNameOpen;
    static QString existFileNameWrite;
};


#endif // FILEOP_H
