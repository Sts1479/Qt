#ifndef SERIALARDUINO_H
#define SERIALARDUINO_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include "QMutex"

#define ARDUINO_COLS_COUNT  13

class SerialArduino : public QObject
{
    Q_OBJECT
public:
    explicit SerialArduino(QObject *parent = 0);

    struct SData{
        /*float reserve1[6];

        float C_7;
        float C_8;
        float res_1;
        float C_10;
        float C_11;
        float res_2;
        float C_13;
        float C_14;
        float reserve2[5];
*/
        float fl[19];
    };

    struct Sxyz{
        float x,y,z;
    };

    struct SArdData{
//        union{
//            struct{
//                Sxyz Gyro_Scalled;
//                Sxyz Accel_Scalled;
//                Sxyz Gyro_angle;
//                Sxyz Accel_Angle;
//                Sxyz Angle;
//                Sxyz Dunno;
//                float Load;
//            };
            float RawData[ARDUINO_COLS_COUNT];
        //};

    };

    static SArdData GetData();

signals:
    void DataRecieved();

public slots:
    void init(); // Инициализация по умолчанию
    void configure(int Baudrate, QSerialPort::DataBits databits, QSerialPort::Parity parity, QSerialPort::StopBits stopbits, QSerialPort::FlowControl flowcontrol); // Конфигурирование порта
    void readData();
private:
    QSerialPort* serialPort;
    QList<QSerialPortInfo> avPorts;
    QString m_RxStringBuf;
    static QMutex m_Mutex;

    static SArdData m_ArdData;

    quint32 m_RowCounter = 0;
};

#endif // SERIALARDUINO_H
