#include "qparsecoursewarefileop.h"
#include "qparsecousewarefile.h"
#include <qDebug>

QParseCourseWareFileWork::QParseCourseWareFileWork(QObject *parent) : QObject(parent)
{

}

void QParseCourseWareFileWork::DoParseCourseWareFile(QString strPath, QMap<QString, QCoursewareInfo > *mapCoursewareInfo)
{
    QParseCousewareFile parseFile;
    parseFile.ParseFile(strPath,mapCoursewareInfo);
    emit Finish();
}




//--------------------------------------------------------------

QParseCourseWareFileOp::QParseCourseWareFileOp(QObject *parent) : QObject(parent)
{
    workerThread.start();
}

QParseCourseWareFileOp::~QParseCourseWareFileOp()
{
    workerThread.requestInterruption();
    workerThread.quit();
    workerThread.wait();
}

void QParseCourseWareFileOp::StartParseFile(QString strPath, QMap<QString, QCoursewareInfo > *mapCoursewareInfo)
{
        QParseCourseWareFileWork* pParseFileWork = new QParseCourseWareFileWork;
        pParseFileWork->moveToThread(&workerThread);

        connect(&workerThread, &QThread::finished, pParseFileWork, &QObject::deleteLater);
        connect(this, &QParseCourseWareFileOp::ParseFile, pParseFileWork, &QParseCourseWareFileWork::DoParseCourseWareFile);
        connect(pParseFileWork,&QParseCourseWareFileWork::Finish,this,&QParseCourseWareFileOp::Finish);

        emit ParseFile(strPath,mapCoursewareInfo);
}

void QParseCourseWareFileOp::Finish()
{
    emit ParseFinish();
}
