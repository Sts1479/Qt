#include "serialarduino.h"
#include "QTime"

QMutex SerialArduino::m_Mutex;
SerialArduino::SArdData SerialArduino::m_ArdData;

SerialArduino::SerialArduino(QObject *parent) :
    QObject(parent)
{


}

void SerialArduino::init(){


    serialPort = new QSerialPort;
    // Поиск даступных портов------------------------------------------------------------
    avPorts = QSerialPortInfo::availablePorts();
     qDebug()<<"avPorts.size()="<<avPorts.size();
    if (avPorts.size()>0){
        // Захват первого  попавшегося порта---------------------------------------------
        serialPort->setPortName("ttyACM0");
        ///serialPort->setReadBufferSize(1024*8);
        if (serialPort->open(QIODevice::ReadWrite)) {
                  // Конфигурирование порта
            //configure(115200,QSerialPort::Data8,QSerialPort::NoParity,QSerialPort::OneStop,QSerialPort::NoFlowControl);
            configure(QSerialPort::Baud115200,QSerialPort::Data8,QSerialPort::NoParity,QSerialPort::OneStop,QSerialPort::NoFlowControl);
            //serialPort->setReadBufferSize(1024*16);
            qDebug()<<"ARDUINO opened";
        }else qDebug()<<"Can not open port Arduino";
    }else {
        qDebug()<<"No serial port found";
    }
    //----------------------------------------------------------------------------------
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));

}

// Конфигурирование порта
void SerialArduino::configure(int Baudrate,QSerialPort::DataBits databits,QSerialPort::Parity parity,QSerialPort::StopBits stopbits,QSerialPort::FlowControl flowcontrol){
    serialPort->setBaudRate(Baudrate);
    serialPort->setDataBits(databits);
    serialPort->setParity(parity);
    serialPort->setStopBits(stopbits);
    serialPort->setFlowControl(flowcontrol);
    QString temp = "Serial port configured, Name: ";    temp += serialPort->portName();
    temp += ", Baud_Rate: ";      temp += QString::number(serialPort->baudRate());
    temp += ", Data Bits: ";      temp += QString::number(serialPort->dataBits());
    temp += ", Parity ";          temp += QString::number(serialPort->parity());
    temp += ", Flow control ";    temp += QString::number(serialPort->flowControl());
    temp += ", Stop Bits ";       temp += QString::number(serialPort->stopBits());
    qDebug()<<temp;
}

// Чтение данных из порта
void SerialArduino::readData()
{
    //--------------------------------------------------------------------------------------------------------------------------
    QByteArray byteArray = serialPort->readAll();
    //qDebug()<<"RCV"<<QString(byteArray);
    m_RxStringBuf.append(QString(byteArray));

   // qDebug()<<"Inp Buffer"<<QTime::currentTime()<<m_RxStringBuf;

    QList<QString> StringList = m_RxStringBuf.split("\r\n");

    if (StringList.size() > 2)    //remove all exept two last
    {
        for (int i = 0;i <StringList.size() - 2; i++){
            StringList.removeAt(0);
        }
    }


    if (StringList.size()>0){
        //qDebug()<<"firstString"<<StringList.first();
        QList<QString> Row = StringList.last().split("\t");
        //qDebug()<<"Row.Size"<<Row.size();
        //qDebug()<<"2d row size"<<Row.size();
        if (Row.size() == ARDUINO_COLS_COUNT){

            m_Mutex.lock();

            for (int i = 0; i<ARDUINO_COLS_COUNT;i++){
                m_ArdData.RawData[i] = Row.at(i).toFloat();

                m_RowCounter++;
            }

            m_Mutex.unlock();
            //qDebug()<<"Data RCV";
            emit DataRecieved();
            //m_RxStringBuf = StringList.join("\r\n");
            m_RxStringBuf = "";
        }else{
            QList<QString> Row = StringList.first().split("\t");
            //qDebug()<<"1st row size"<<Row.size();
            if (Row.size() == ARDUINO_COLS_COUNT){

                m_Mutex.lock();

                for (int i = 0; i<ARDUINO_COLS_COUNT;i++){
                    m_ArdData.RawData[i] = Row.at(i).toFloat();

                    m_RowCounter++;
                }

                m_Mutex.unlock();
                //qDebug()<<"Data RCV";
                emit DataRecieved();
                StringList.removeFirst();
                //m_RxStringBuf = StringList.join("\r\n");
                m_RxStringBuf = StringList.last();
            }/*else{
                //m_RxStringBuf = "";
                //qDebug()<<"Error: WRONG MSG SIZE";
            }*/
        }
    }


    /*qDebug()<<"byteArray size"<<byteArray.size()<<QTime::currentTime();
    //QString dataString(byteArray.toHex());
    //qDebug()<<"serial read - "<<dataString<<" time="<<QTime::currentTime();

    QString QSbuf(byteArray.toHex());
    for (int i = 2; i < QSbuf.size(); i += 3) QSbuf.insert(i, ' ');
    qDebug()<<QTime::currentTime().toString()+":"+QString::number(QTime::currentTime().msec())<<"INPUT"<<QSbuf.toUpper();


    MRXBuf.append(byteArray);
    if (MRXBuf.size()>=sizeof(SData))
    {
        emit DataRecieved(MRXBuf.mid(0,76));
        //qDebug()<<"datarecieved"<<QTime::currentTime();
                  MRXBuf.remove(0,76);
    }*/
}

SerialArduino::SArdData SerialArduino::GetData(){
    QMutexLocker Locker(&m_Mutex);
    return m_ArdData;
}

