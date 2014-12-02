#ifndef TCPCOMMAND_H
#define TCPCOMMAND_H

#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>

class TcpCommand : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpCommand(QObject *parent = 0);

signals:
    void signTcpError(QString);

public slots:
    //建立tcp连接
    void tcpCreate();
    //读tcp数据
    void tcpRead();
    //设置启动命令
    void tcpCmdStart();
    //设置回传命令
    void tcpCmdBack();
    //设置停止命令
    void tcpCmdStop();
    //关闭tcp连接
    void tcpClose();
    //设置tcp的ip地址
    void tcpIp(QString ip);
    //设置tcp的port
    void tcpPort(quint32 port);
    //设置当前频点
    void tcpFreq(quint32 freq);

     void displayError(QAbstractSocket::SocketError);

private:
    char m_startCmd[12];
    char m_backCmd[12];
    char m_stopCmd[12];

    quint32 m_freq;
    QString m_ip;
    quint32 m_port;
};

#endif // TCPCOMMAND_H
