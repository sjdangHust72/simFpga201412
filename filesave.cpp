#include "filesave.h"
#include <QDebug>

FileSave::FileSave(QObject *parent) :
    QObject(parent)
{
    cnt = 0;
}

FileSave::~FileSave()
{
    m_file->close();
}


void FileSave::slotFileRevFileName(QString s)
{
    m_fileName = s;
    m_file = new QFile(m_fileName);
    if(!m_file->isOpen())
    {
        if(!m_file->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qDebug()<<"file open fail";
            return ;
        }
    }
}

void FileSave::slotFileRevSrcData(QByteArray datagram)
{

    //qDebug()<<"srcData:"<<datagram.at(11)*256+datagram.at(10);
    QDataStream stm(m_file);
    stm.writeRawData(datagram.data(),datagram.size());
    if(datagram.size()!=1024)
        qDebug()<<"error at:"<<datagram.at(11)*256+datagram.at(10);

    m_file->flush();
    cnt++;
    emit signFileWriteTime(cnt);
}

void FileSave::slotFileClose()
{
    if(m_file->isOpen())
        m_file->close();
}

void FileSave::slotFileOpen()
{
    if(!m_file->isOpen())
    {
        if(!m_file->open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qDebug()<<"file open fail";
            return ;
        }
    }

}

/*
void FileSave::slotFileRevSrcData(QByteArray datagram)
{
    qDebug()<<"srcData:"<<datagram.at(11)*256+datagram.at(10);
    if(!isRcd && datagram.at(11)*256+datagram.at(10) == 1)
    {
        isRcd = true;
        m_filedata.push_back(datagram);

    }
    else if(!isRcd && datagram.at(11)*256+datagram.at(10) != 1)
    {
        if(datagram.at(11)*256+datagram.at(10) == 38)
        {
            isRcd = false;
            datagram.clear();
        }
    }
    else if(isRcd)
    {
        if(datagram.at(11)*256+datagram.at(10) != 38)
        {
            m_filedata.push_back(datagram);
        }
        else
        {
            m_filedata.push_back(datagram);
            isRcd = false;
            //save
            QFile file(m_fileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                return ;
            }
            QDataStream stm(&file);
            stm.writeRawData(m_filedata.data(),m_filedata.size());

            file.close();
            m_filedata.clear();
            m_filedata.resize(38*1024);
        }
    }
}
*/


