#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init label_connect
    ui->label_connect->setText("state:not connect");

    //init menu start
    ui->actionLocal->setChecked(true);
    connect(ui->actionFpga,SIGNAL(triggered()),this,SLOT(slotFpga()));
    connect(ui->actionLocal,SIGNAL(triggered()),this,SLOT(slotLocal()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//tcp error
void MainWindow::slotTcpMsg(QString str)
{
    QMessageBox::information(this, "Error", str, QMessageBox::Ok , QMessageBox::Ok);
    if(ui->pbtn_connect->text() == "close")
    {
        ui->pbtn_connect->setText("connect");
        ui->label_connect->setText("state:not connect");
        emit signTcpClose();
    }
}

void MainWindow::slotFpga()
{
    ui->actionLocal->setChecked(false);
    emit signTcpClose();
}

void MainWindow::slotLocal()
{
    ui->actionFpga->setChecked(false);
}



void MainWindow::on_pbtn_connect_clicked()
{

    if(ui->pbtn_connect->text() == "connect")
    {//非连接状态-->连接状态
        //do something
        //判断开始菜单里面连接是 fpga or local
        if(ui->actionFpga->isChecked())
        {//fpga
            emit signCurIp("128.0.43.43");
        }
        else
        {//local
            emit signCurIp("127.0.0.1");
        }
        //设置port
        emit signCurTcpPort(4096);
        emit signCurUdpPort(4098);
        emit signCurFreq(505);
        //tcp连接
        emit signTcpCreate();
        //udp打开
        emit signUdpOpen();

        //then,setting button and label
        ui->label_connect->setText("state:connecting");
        ui->pbtn_connect->setText("close");
    }
    else if(ui->pbtn_connect->text() == "close")
    {//连接状态-->非连接状态
        //do something
        //tcp close
        emit signTcpClose();
        //udp close
        emit signUdpClose();

        //then,settting button and label
        ui->label_connect->setText("state:not connect");
        ui->pbtn_connect->setText("connect");
    }
}
