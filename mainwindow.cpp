#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>


extern TcpCommand *gTcp;
extern QThread *gFileThd;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"main thread id:"<<QThread::currentThreadId();
    //init label_connect
    ui->label_connect->setText("-*-*-*-");

    //ip设置
    ui->lineEdit_ipAddr->setText(tr("127.0.0.1"));
    ui->lineEdit_tcpPort->setText("4096");
    ui->lineEdit_udpPort->setText("4098");

    ui->pbtn_connect->setText("open");
    //频率设置
    int cnt=0;
    for (double i=50.5;i<100.0;i+=7,cnt++)
    {
        m_dFreqDot[cnt] = i;
    }
    for (double i=107.5;i<300.0;i+=7,cnt++)
    {
        m_dFreqDot[cnt] = i;
    }
    for (double i=306.0;i<605.0;i+=8,cnt++)
    {
        m_dFreqDot[cnt] = i;
    }

    for(int i=0;i<74;i++)
    {
        ui->comboBox_freqSetting->addItem(QString::number(m_dFreqDot[i],'f',1));
    }

    //次数
    ui->lineEdit_colTimes->setText("10");

    //开始按钮
    ui->pbtn_start->setDisabled(true);
    //停止按钮
    ui->pbtn_stop->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//tcp state change
void MainWindow::slotStateChange(QAbstractSocket::SocketState id)
{

    if(id == QAbstractSocket::UnconnectedState)
    {
        ui->label_connect->setText("Unconnected");
        qDebug()<<"Unconnected!";

        //ui connect
        ui->pbtn_connect->setDisabled(false);

        ui->lineEdit_ipAddr->setDisabled(false);
        ui->lineEdit_tcpPort->setDisabled(false);
        ui->lineEdit_udpPort->setDisabled(false);

        ui->pbtn_connect->setText("open");

        //ui 【开始】 和 【停止】 按钮禁止
        ui->pbtn_start->setDisabled(true);
        ui->pbtn_stop->setDisabled(true);
    }
    else if(id == QAbstractSocket::HostLookupState)
    {
        ui->label_connect->setText("HostLookup");
        qDebug()<<"HostLookup!";
    }
    else if(id == QAbstractSocket::ConnectingState)
    {
        ui->label_connect->setText("Connecting");
        qDebug()<<"Connecting!";
    }
    else if(id == QAbstractSocket::ConnectedState)
    {
        ui->label_connect->setText("Connected");
        qDebug()<<"Connected!";

        //ui close
        ui->pbtn_connect->setText("close");
        ui->pbtn_connect->setDisabled(false);

        //ui 【开始】 和 【停止】 按钮使能
        ui->pbtn_start->setDisabled(false);
        ui->pbtn_stop->setDisabled(false);
    }
    else if(id == QAbstractSocket::BoundState)
    {
        ui->label_connect->setText("Bound");
        qDebug()<<"Bound!";
    }
    else if(id == QAbstractSocket::ClosingState)
    {
        ui->label_connect->setText("Closing");
        qDebug()<<"Closing!";


    }
    else if(id == QAbstractSocket::ListeningState)
    {
        ui->label_connect->setText("ListeningState");
        qDebug()<<"ListeningState!";
    }
    else
    {
        qDebug()<<"NotHaveThisStage!";
    }
}

void MainWindow::slotErrorString(QAbstractSocket::SocketError)
{
    QMessageBox::information(this, "Error", gTcp->errorString(), QMessageBox::Ok , QMessageBox::Ok);
}



void MainWindow::on_pbtn_connect_clicked()
{

    if(gTcp->state() == QAbstractSocket::UnconnectedState)
    {//非连接状态-->连接状态
        //1.get ip
        QString ip = ui->lineEdit_ipAddr->text();
        quint32 tcpPort = ui->lineEdit_tcpPort->text().toInt();
        quint32 udpPort = ui->lineEdit_udpPort->text().toInt();
        qDebug()<<"ip:"<<ip<<endl<<"tcpPort:"<<tcpPort<<endl<<"udpPort:"<<udpPort<<endl;

        //disable lineEdits
        ui->lineEdit_ipAddr->setDisabled(true);
        ui->lineEdit_tcpPort->setDisabled(true);
        ui->lineEdit_udpPort->setDisabled(true);

        emit signCurIp(ip);
        emit signCurTcpPort(tcpPort);
        emit signCurUdpPort(udpPort);

        //tcp连接
        emit signTcpCreate();
        //udp打开
        emit signUdpOpen();

        //ui connect disable
        ui->pbtn_connect->setDisabled(true);
    }
    else if(gTcp->state() == QAbstractSocket::ConnectedState)
    {//连接状态-->非连接状态
        //tcp close
        emit signTcpClose();
        //udp close
        emit signUdpClose();

        //ui connect disable
        ui->pbtn_connect->setDisabled(true);
    }
}




void MainWindow::on_cb_record_toggled(bool checked)
{
    if(checked == true)
    {
        //保存的文件名字
        m_fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"../",tr("DAT (*.dat *DAT)"));
        if(m_fileName == "")
        {
            qDebug()<<"Not select any file or input new file name";
            ui->cb_record->setChecked(false);
            return ;
        }

        QFile *m_file = new QFile(m_fileName);
        if(!m_file->exists())
        {
            m_file->open(QIODevice::WriteOnly);
            m_file->close();
        }
        if(!m_file->open(QIODevice::WriteOnly))
        {
            qDebug()<<"Can't not open "<<m_fileName;
            return ;
        }
        m_file->close();
        ui->lineEdit_ipInfo->setText(m_fileName);

        //发送文件名
        emit signFileName(m_fileName);
    }
}

void MainWindow::on_pbtn_start_clicked()
{
    //开始按钮
    //检查文件
    if(m_fileName == "")
    {
        QMessageBox::information(this, "Error", "set current file name", QMessageBox::Ok , QMessageBox::Ok);
        return ;
    }
    //发送freq
    int idxFreq = ui->comboBox_freqSetting->currentIndex();
    emit signCurFreq((quint32)(m_dFreqDot[idxFreq] * 10));
    qDebug()<<"emit freq :"<<m_dFreqDot[idxFreq];

    //启动tcp
    emit signTcpStart();
    emit signTcpBack();

    //保存文件线程
    emit signFileThdStart();
    gFileThd->start();
}

void MainWindow::on_pbtn_stop_clicked()
{
    //停止按钮
    //停止tcp
    emit signTcpStop();

    emit signFileThdStop();
    //保存文件
    gFileThd->quit();
    gFileThd->wait();
}
