#ifndef QPARSECOUSEWAREFILE_H
#define QPARSECOUSEWAREFILE_H

#include <QString>
#include "qcoursewareinfo.h"

//--------------------解析课件目录文件--------------------------------

class QParseCousewareFile
{
public:
    QParseCousewareFile();
public:
    //解析文件中的课件到map中
    bool ParseFile(QString strPath,QMap<QString,QCoursewareInfo>* mapCoursewareInfo = 0);
protected:
    //解析json数据
    int ParseCousewareJson(const QJsonObject  &childObject);
    //将找到的课件放入map
    void PutCousewareListToHash(const QJsonValue &childValue);
protected:
    QMap<QString,QCoursewareInfo>* m_ptrMapCoursewareInfo;
};

#endif // QPARSECOUSEWAREFILE_H
