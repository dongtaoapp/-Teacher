#include "qparsecousewarefile.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QThread>
#include <QMessageBox>
QParseCousewareFile::QParseCousewareFile()
{
    m_ptrMapCoursewareInfo = 0;
}

bool QParseCousewareFile::ParseFile(QString strPath, QMap<QString, QCoursewareInfo> *mapCoursewareInfo)
{
    m_ptrMapCoursewareInfo = mapCoursewareInfo;

    QFile file(strPath);
    bool bOpen = file.open(QIODevice::ReadOnly);
    if(!bOpen)
    {
        return false;
    }
    QByteArray filedata = file.readAll();

    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(filedata,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isObject())
        {
            QJsonObject rootObj = jDoc.object();
            if (rootObj.contains("CoursewareList"))
            {

                QJsonValue root = rootObj.value("CoursewareList");

                if(root.isObject())
                {
                    QJsonObject  childObject = root.toObject();
                    ParseCousewareJson(childObject);

                }

            }

        }

    }
    else
    {
        file.close();
        return false;
    }

    file.close();

    return true;
}

int QParseCousewareFile::ParseCousewareJson(const QJsonObject &childObject)
{
    if (childObject.contains("Courseware"))
    {

        QJsonValue CoursewareValue = childObject.value("Courseware");
        if(CoursewareValue.isArray())
        {
            QJsonArray jsonArray = CoursewareValue.toArray();
            int num=jsonArray.count();
            for (int i = 0; i < num;i++)
            {
                QJsonValue childValue = jsonArray[i];
                PutCousewareListToHash(childValue);
            }
            return num;
        }
        else /*if(CoursewareValue.isObject())*/
        {
            PutCousewareListToHash(CoursewareValue);
              return 1;
        }

    }
     return 0;
}

void QParseCousewareFile::PutCousewareListToHash(const QJsonValue &childValue)
{
   QJsonObject chObject = childValue.toObject();
   int num= ParseCousewareJson(chObject);
   QCoursewareInfo pInfo;
    pInfo.sonClsaa=num;
    if(chObject.contains("NetID"))
    {
        QJsonValue value = chObject.value("NetID");
        if (value.isString())
        {
            pInfo.m_strNetId = value.toString();
        }
    }
    if(chObject.contains("Name"))
    {
        QJsonValue value = chObject.value("Name");
        if (value.isString())
        {
             pInfo.m_strCoursewareName = value.toString();
        }
    }

    if(chObject.contains("TreeDir"))
    {
        QJsonValue value = chObject.value("TreeDir");
        if (value.isString())
        {
            pInfo.m_strTreeDir = value.toString();
        }
    }

    if(chObject.contains("Flash"))
    {
        QJsonValue value = chObject.value("Flash");
        if (value.isString())
        {
            pInfo.m_strFlash = value.toString();
        }
    }
    if(chObject.contains("defalut_sound"))
    {
        QJsonValue value= chObject.value("defalut_sound");
        if(value.isString())
        {
            pInfo.m_defalut_sound=value.toString();
        }
    }
    if(chObject.contains("tremble_position"))
    {
        pInfo.m_tremble_position=chObject.value("tremble_position").toString();
    }
    if(chObject.contains("CaseId"))
    {
        pInfo.m_CaseID=chObject.value("CaseId").toString();
    }
    if(chObject.contains("sound_list"))
    {
         QJsonArray array=chObject.value("sound_list").toArray();
        pInfo.m_sound_list=QJsonDocument(array).toJson();
    }


    m_ptrMapCoursewareInfo->insert(pInfo.m_strTreeDir,pInfo);
}
