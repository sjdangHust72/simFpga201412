#ifndef FILESAVE_H
#define FILESAVE_H

#include <QObject>
#include <QFile>

class FileSave : public QObject
{
    Q_OBJECT
public:
    explicit FileSave(QObject *parent = 0);
    ~FileSave();
signals:
    void signFileWriteTime(quint32);
public slots:

    void slotFileRevFileName(QString);
    void slotFileRevSrcData(QByteArray);
    void slotFileClose();
    void slotFileOpen();
private:
    QString m_fileName;
    QFile *m_file;
    int cnt;
};

#endif // FILESAVE_H
