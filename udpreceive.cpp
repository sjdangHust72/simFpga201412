#include "udpreceive.h"
#include <QThread>

UdpReceive::UdpReceive(QObject *parent) :
    QUdpSocket(parent)
{
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(readData()));

}

//udp port
void UdpReceive::udpPort(quint32 port)
{
    m_port = port;
    qDebug()<<"udp port:"<<m_port;
}
//udp current freq
void UdpReceive::udpFreq(quint32 freq)
{
    m_freq = freq;
    qDebug()<<"udp freq:"<<m_freq;
}
//udp open
void UdpReceive::udpOpen()
{
    this->bind(m_port,QUdpSocket::DontShareAddress);
    qDebug()<<"udp open";
}
//udp close
void UdpReceive::udpClose()
{
    this->close();
    qDebug()<<"udp close";
}
//udp read data
void UdpReceive::readData()
{
    //static quint32 cnt = 0;
    while (hasPendingDatagrams())
    {
        QByteArray datagram;
        if(1024 == pendingDatagramSize())
        {
            datagram.resize(1024);
            readDatagram(datagram.data(),1024);

            //发送原始1k数据
            emit signUdpSrcData(datagram);
            //qDebug()<<"udp thread id:"<<QThread::currentThreadId();
            //qDebug()<<"udp read data"<<cnt;
            //cnt++;
        }
        else
        {
            datagram.resize(pendingDatagramSize());
            readDatagram(datagram.data(), datagram.size());
        }
    }

}
