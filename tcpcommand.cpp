#include "tcpcommand.h"

TcpCommand::TcpCommand(QObject *parent) :
    QTcpSocket(parent)
{
    // 22启动命令 6020  0.1M        1000ms
    quint8 Start[12]   =   {0X5A,0XA5,0X5B,0XB5,0X22,0X00,0X17,0X84,0X17,0X84,0X03,0XE8};
    for(int i=0;i<12;i++)
        m_startCmd[i] = Start[i];

    // 24回传命令                                          无限回传
    quint8 Back[12]    =   {0X5A,0XA5,0X5B,0XB5,0X24,0X00,0XF0,0X0A};
    for(int i=0;i<12;i++)
        m_backCmd[i] = Back[i];

    // 23 stop command
    quint8 Stop[12]    =   {0X5A,0XA5,0X5B,0XB5,0X23,0X00,0XF0,0X0A};
    for(int i=0;i<12;i++)
        m_stopCmd[i] = Stop[i];

    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(tcpRead()));
    QObject::connect(this,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}
//ip address
void TcpCommand::tcpIp(QString ip)
{
    m_ip = ip;
}
// port
void TcpCommand::tcpPort(quint32 port)
{
    m_port = port;
}
//current freq
void TcpCommand::tcpFreq(quint32 freq)
{
    m_freq = freq;
}

void TcpCommand::tcpCreate()
{
    const int DYTIME = 10000;//delay time
    const int CTTIME = 10;   //try connecting time
    qDebug()<<"tcp ip:"<<m_ip;
    qDebug()<<"tcp port:"<<m_port;
    //1.abort tcp all connect
    this->abort();
    //2.connect host address
    this->connectToHost(QHostAddress(this->m_ip),this->m_port);
}

void TcpCommand::tcpRead()
{
    QByteArray qba = this->readAll();
    qDebug()<<"[tcp thread:]"<<qba;
}

//关闭命令
void TcpCommand::tcpClose()
{
    this->close();
}



//启动命令
void TcpCommand::tcpCmdStart()
{
    //修改频点
    m_startCmd[6] = m_startCmd[8] = (m_freq)/256;
    m_startCmd[7] = m_startCmd[9] = (m_freq)%256;
    //发送命令
    this->write(m_startCmd,12);
}
//回传命令
void TcpCommand::tcpCmdBack()
{
    this->write(m_backCmd,12);
    qDebug("backCmd:%s",m_backCmd);
}

//停止命令
void TcpCommand::tcpCmdStop()
{
    this->write(m_stopCmd,12);
    qDebug("stopCmd:%s",m_stopCmd);
}

void TcpCommand::displayError(QAbstractSocket::SocketError)
{
    qDebug() << this->errorString(); //输出错误信息
    emit signTcpError(this->errorString());
}
