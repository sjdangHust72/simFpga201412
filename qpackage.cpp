#include "qpackage.h"

QPackage::QPackage()
{
    memset(head,0,sizeof(head));
    memset(data,0,sizeof(data));
    isPack = false;
}

QPackage::QPackage(const QPackage &pkg)
{
    memcpy((void*)head,(void*)pkg.getHeadAddr(),sizeof(head));
    memcpy((void*)data,(void*)pkg.getDataAddr(),sizeof(data));
    isPack = pkg.isPacking();
}

QPackage::~QPackage()
{

}

void QPackage::Packing(QByteArray datagram)
{
    isPack = true;

    strpk *pt = (strpk*)datagram.data();
    memcpy(head,pt->head,sizeof(head));
    memcpy(data,pt->data,sizeof(data));
}

bool QPackage::isPacking() const
{
    return isPack;
}


