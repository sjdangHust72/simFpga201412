#include "filesave.h"
#include <QDebug>
#include <QFile>

FileSave::FileSave(QObject *parent) :
    QObject(parent)
{
    isRcd = false;
    idx=0;
}


void FileSave::slotFileRevFileName(QString s)
{
    m_fileName = s;
    //qDebug()<<"filename:"<<s;

}

void FileSave::slotFileRevSrcData(QByteArray datagram)
{
    qDebug()<<"srcData:"<<datagram.at(11)*256+datagram.at(10);
    if(!isRcd && datagram.at(11)*256+datagram.at(10) == 1)
    {
        isRcd = true;
        m_filedata->push_back(datagram);

    }
    else if(!isRcd && datagram.at(11)*256+datagram.at(10) != 1)
    {

    }
    else if(isRcd)
    {
        if(datagram.at(11)*256+datagram.at(10) != 38)
        {
            m_filedata->push_back(datagram);
        }
        else
        {
            m_filedata->push_back(datagram);
            isRcd = false;
            //save
            QFile file(m_fileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                return ;
            }
            QDataStream stm(&file);
            stm.writeRawData(m_filedata->data(),m_filedata->size());

            file.close();
            delete m_filedata;
            m_filedata = new QByteArray();
        }
    }
}

void FileSave::slotFileThdStop()
{
    isRcd = false;
    idx = 0;
    delete m_filedata;
}

void FileSave::slotFileThdStart()
{
    isRcd = false;
    idx=0;
    m_filedata = new QByteArray();
}
