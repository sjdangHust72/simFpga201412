#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include "qpackage.h"
#include "qframedata.h"

class Package : public QObject
{
    Q_OBJECT
public:
    explicit Package(QObject *parent = 0);

signals:
    void signPkgData(QPackage);
    void signPkgFrameData(QFrameData);
public slots:
    void slotPkgRevSrcData(QByteArray);

private slots:
    void slotDoFrame(QPackage);
    void slottest(QPackage);

private:
    bool isRcd;
    QFrameData fm;

    quint32 last_index;
    quint32 last_freq;
};

#endif // PACKAGE_H
