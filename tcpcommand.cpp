#include "tcpcommand.h"
#include <QThread>
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

    //tcp data receive: readyRead() <-> tcpRead()
    QObject::connect(this,SIGNAL(readyRead()),this,SLOT(tcpRead()));
}

TcpCommand::~TcpCommand()
{
    tcpCmdStop();
    tcpClose();
}

//ip address
void TcpCommand::tcpIp(QString ip)
{
    m_ip = ip;
    qDebug()<<"tcp ip:"<<m_ip;
}
// port
void TcpCommand::tcpPort(quint32 port)
{
    m_port = port;
    qDebug()<<"tcp port:"<<m_port;
}
//current freq
void TcpCommand::tcpFreq(quint32 freq)
{
    m_freq = freq;
    qDebug()<<"tcp freq:"<<m_freq;
}

void TcpCommand::tcpCreate()
{
    //1.abort tcp all connect
    this->abort();
    //2.connect host address
    this->connectToHost(QHostAddress(this->m_ip),this->m_port);

    qDebug()<<"tcp create";
    qDebug()<<"tcp thread id:"<<QThread::currentThreadId()<<endl;
}

void TcpCommand::tcpRead()
{
    QByteArray qba = this->readAll();
    qDebug()<<hex<<"tcp read data:"<<qba;
}

//关闭命令
void TcpCommand::tcpClose()
{
    this->close();
    qDebug()<<"tcp close";
}



//启动命令
void TcpCommand::tcpCmdStart()
{
    //修改频点
    m_startCmd[6] = m_startCmd[8] = (m_freq)/256;
    m_startCmd[7] = m_startCmd[9] = (m_freq)%256;
    //发送命令
    this->write(m_startCmd,12);
    this->flush();
    this->waitForBytesWritten(1000);
    qDebug("startCmd");
}
//回传命令
void TcpCommand::tcpCmdBack()
{
    this->write(m_backCmd,12);
    this->flush();
    this->waitForBytesWritten(1000);
    qDebug("backCmd");
}

//停止命令
void TcpCommand::tcpCmdStop()
{
    this->write(m_stopCmd,12);
    this->flush();
    this->waitForBytesWritten(1000);
    qDebug("stopCmd");
}







