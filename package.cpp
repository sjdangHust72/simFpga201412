#include "package.h"
#include <QDebug>

Package::Package(QObject *parent) :
    QObject(parent)
{
    isRcd = false;
    //connect(this,SIGNAL(signPkgData(QPackage)),this,SLOT(slottest(QPackage)));
    connect(this,SIGNAL(signPkgData(QPackage)),this,SLOT(slotDoFrame(QPackage)));
}

void Package::slotPkgRevSrcData(QByteArray datagram)
{
    static quint32 cnt=0;
    QPackage pkg;
    pkg.Packing(datagram);
    emit signPkgData(pkg);
    //qDebug()<<"signPkgData:"<<cnt;
    cnt++;
}

void Package::slotDoFrame(QPackage pkg)
{
    //qDebug()<<"slotDoFrame";
    qDebug()<<"package:"<<pkg.getIndex();
    if(!isRcd && pkg.getIndex() == 1)
        {//没有记录的情况下，如果收到了 编号为 1的package
            isRcd = true;
            fm.clear();
            //写入frame
            fm.pushBack(pkg);
            fm.setStartPoint(pkg.getStartPoint());
            fm.setEndPoint(pkg.getEndPoint());
            fm.setRevFreq(pkg.getRevFreq());

            last_index = 1;
            last_freq = pkg.getRevFreq();
        }
        else if(!isRcd && pkg.getIndex() != 1)
        {//没有记录的情况下，如果收到的package的编号不为1
            //丢弃
        }
        else if(isRcd)
        {//记录的情况下
            if(pkg.getIndex() != 38)
            {
                //检查是否为同一组,同一个频率
                if(last_freq == pkg.getRevFreq() && last_index+1 == pkg.getIndex())
                {//此组为正确的组
                    fm.pushBack(pkg);

                    last_index = pkg.getIndex();//the number(1-38)
                }
                else
                {
                    isRcd = false;
                    //清空 frame
                    fm.clear();

                    last_index = 0;//the number(1-38)
                    last_freq = 0;//receive freq,unit is 100k
                }
            }
            else if(pkg.getIndex() == 38)
            {
                fm.pushBack(pkg);

                //frame is already,we shall do something
                emit signPkgFrameData(fm);
                qDebug()<<"send framedata by 9364";
                isRcd = false;
                last_index = 0;//the number(1-38)
                last_freq = 0;//receive freq,unit is 100k
            }
        }
}

void Package::slottest(QPackage pkg)
{
    qDebug()<<"start point:"<<pkg.getStartPoint();
    qDebug()<<"end point:"<<pkg.getEndPoint();
}
