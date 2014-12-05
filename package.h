#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>


class Package : public QObject
{
    Q_OBJECT
public:
    explicit Package(QObject *parent = 0);
    Package(QByteArray &datagram);

signals:

public slots:
    quint16 getStartPoint()const {return sp;}
    quint16 getEndPoint()const {return ep;}
    quint16 getFreqLen()const {return len;}
    quint16 getPackageGrp()const{return packgrp;}
    quint16 getNumInPackage()const{return numInpack;}
    quint16 getRevFreq()const {return recFreq;}
    quint32 *getDataAddr(){return data;}
private:
    quint16 head;
    quint16 sp; //start point in 65536
    quint16 ep; //end poin in 65536
    quint16 len;//len of freq in 65536
    quint16 packgrp;//the group number
    quint16 numInpack;//the number(1-38)
    quint16 recFreq;//receive freq,unit is 100k
    quint32 data[252];

    struct package{
        quint16 head[8];
        quint32 data[252];
    };
    package *pkg;
};

#endif // PACKAGE_H
