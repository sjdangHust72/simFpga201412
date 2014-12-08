#ifndef QFRAMEDATA_H
#define QFRAMEDATA_H

#include <QtGlobal>
#include <QMetaType>
#include <qpackage.h>

class QFrameData
{
public:
    QFrameData();
    QFrameData(const QFrameData&);
    ~QFrameData();

    quint16 getStartPoint()const{return head[1];}
    quint16 getEndPoint()const{return head[2];}
    quint16 getRevFreq()const{return head[3];}
    void setStartPoint(quint16 val){head[1] = val;}
    void setEndPoint(quint16 val){head[2] = val;}
    void setRevFreq(quint16 val) {head[3] = val;}

    const quint16 *getHeadAddr()const{return head;}
    const quint32 *getDataAddr()const{return data;}
    const char* getDataRawAddr()const{return (char*)data;}

    quint32 getCurIdx()const{return idx;}
    void pushBack(QPackage);
    void clear();
private:
    quint16 head[8];
    quint32 data[9364];
    quint32 idx;
};
Q_DECLARE_METATYPE(QFrameData)
#endif // QFRAMEDATA_H
