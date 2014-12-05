#include "package.h"

Package::Package(QObject *parent) :
    QObject(parent)
{
}

Package::Package(QByteArray &datagram)
{
    pkg = (package*)datagram.data();

    head = pkg->head[0];
    sp = pkg->head[1];
    ep = pkg->head[2];
    len = pkg->head[3];
    packgrp = pkg->head[4];
    numInpack = pkg->head[5];
    recFreq = pkg->head[6];

    memcpy(data,pkg->data,sizeof(quint32)*252);

}
