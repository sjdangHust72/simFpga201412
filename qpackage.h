#ifndef QPACKAGE_H
#define QPACKAGE_H
#include <QtGlobal>
#include <QMetaType>

class QPackage
{
public:
    QPackage();
    QPackage(const QPackage&);
    ~QPackage();

    void Packing(QByteArray);

    quint16 getStartPoint()const{return head[1];}
    quint16 getEndPoint()const{return head[2];}
    quint16 getLenth()const{return head[3];}
    quint16 getGroup()const{return head[4];}
    quint16 getIndex()const{return head[5];}
    quint16 getRevFreq()const{return head[6];}

    const quint16 *getHeadAddr()const{return head;}
    const quint32 *getDataAddr()const{return data;}
    bool isPacking()const;
private:
    struct strpk
    {
        quint16 head[8];
        quint32 data[252];
    };
    quint16 head[8];
    quint32 data[252];
    bool isPack;
};
Q_DECLARE_METATYPE(QPackage)
#endif // QPACKAGE_H
