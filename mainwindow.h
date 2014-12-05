#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QFile>
#include "tcpcommand.h"
#include "udpreceive.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    //当前采集频点
    void signCurFreq(quint32 freq);
    //当前连接的IP地址
    void signCurIp(QString str);
    //===============================
    //当前TCP的port
    void signCurTcpPort(quint32 port);
    //tcp建立
    void signTcpCreate();
    //tcp启动
    void signTcpStart();
    //tcp回传
    void signTcpBack();
    //tcp停止
    void signTcpStop();
    //tcp关闭
    void signTcpClose();
    //===============================
    //当前UDP的port
    void signCurUdpPort(quint32 port);
    //udp open
    void signUdpOpen();
    //udp close
    void signUdpClose();

public slots:
    void on_pbtn_connect_clicked();

    //tcp state
    void slotStateChange(QAbstractSocket::SocketState id);
    //tcp error
    void slotErrorString(QAbstractSocket::SocketError);

private slots:
    void on_cb_record_toggled(bool checked);
    void on_pbtn_start_clicked();
    void on_pbtn_stop_clicked();

private:
    Ui::MainWindow *ui;
    double m_dFreqDot[74];

    QString m_fileName;
    QFile m_file;
};

#endif // MAINWINDOW_H
