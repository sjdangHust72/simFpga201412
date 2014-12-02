#ifndef UDPRECEIVE_H
#define UDPRECEIVE_H

#include <QUdpSocket>
#include <QDebug>

class UdpReceive : public QUdpSocket
{
    Q_OBJECT
public:
    explicit UdpReceive(QObject *parent = 0);

public slots:
    //udp port
    void udpPort(quint32 port);
    //得到当前频点，判断接受是否统一
    void udpFreq(quint32 freq);
    //udp 开
    void udpOpen();
    //udp 关
    void udpClose();

    //udp 读
    void readData();

private:
    quint32 m_port;
    quint32 m_freq;

};

#endif // UDPRECEIVE_H
