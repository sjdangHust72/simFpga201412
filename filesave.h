#ifndef FILESAVE_H
#define FILESAVE_H

#include <QObject>
class FileSave : public QObject
{
    Q_OBJECT
public:
    explicit FileSave(QObject *parent = 0);

signals:

public slots:

    void slotFileRevFileName(QString);
    void slotFileRevSrcData(QByteArray);
    void slotFileThdStop();
    void slotFileThdStart();
private:
    QString m_fileName;
    QByteArray *m_filedata;
    bool isRcd;
    int idx;
};

#endif // FILESAVE_H
