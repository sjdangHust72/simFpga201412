#include "qframedata.h"

QFrameData::QFrameData()
{
    idx = 0;
}

QFrameData::QFrameData(const QFrameData &fm)
{
    memcpy(head,fm.getHeadAddr(),sizeof(head));
    memcpy(data,fm.getDataAddr(),sizeof(data));
    idx = fm.getCurIdx();

    setStartPoint(fm.getStartPoint());
    setEndPoint(fm.getEndPoint());
    setRevFreq(fm.getRevFreq());
}

QFrameData::~QFrameData()
{

}

void QFrameData::pushBack(QPackage pkg)
{
    if(idx != 37)
    {
        memcpy(&data[idx*252],pkg.getDataAddr(),sizeof(quint32)*252);
    }
    else//idx == 37
    {
        memcpy(&data[idx*252],pkg.getDataAddr(),sizeof(quint32)*40);
    }
    idx++;
}

void QFrameData::clear()
{
    memset(head,0,sizeof(head));
    memset(data,0,sizeof(data));
    setEndPoint(0);
    setStartPoint(0);
    setRevFreq(0);

    idx = 0;
}
