#ifndef QPARSECOURSEWAREFILEOP_H
#define QPARSECOURSEWAREFILEOP_H

#include <QObject>
#include "qcoursewareinfo.h"
#include <QThread>


//class QCoursewareInfo;
class QParseCourseWareFileWork : public QObject
{
    Q_OBJECT
public:
    explicit QParseCourseWareFileWork(QObject *parent = 0);

signals:
    void Finish();
public slots:
    void DoParseCourseWareFile(QString strPath,QMap<QString,QCoursewareInfo>* mapCoursewareInfo = 0);
};

//--------------------------------------------------------------

class QParseCourseWareFileOp : public QObject
{
    Q_OBJECT
protected:
    QThread workerThread;
public:
    explicit QParseCourseWareFileOp(QObject *parent = 0);
    ~QParseCourseWareFileOp();
public:
    void StartParseFile(QString strPath,QMap<QString,QCoursewareInfo>* mapCoursewareInfo = 0);
signals:
    void ParseFile(QString strPath,QMap<QString,QCoursewareInfo>* mapCoursewareInfo = 0);
    void ParseFinish();
public slots:
    void Finish();
};

#endif // QPARSECOURSEWAREFILEOP_H
