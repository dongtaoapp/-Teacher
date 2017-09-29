#include "qparseinfofromweb.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <qDebug>

QParseInfoFromWeb::QParseInfoFromWeb()
{

}
QParseInfoFromWeb::~QParseInfoFromWeb()
{

}
void QParseInfoFromWeb::ParseUsedefineCousewareInfo(const QByteArray &info, QList<userCourseware *> *lstUserCourseware)
{
    if(info.isEmpty())
    {
        return;
    }
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(info,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isArray())
        {
            QJsonArray jsonArray = jDoc.array();
            for (int i = 0; i < jsonArray.count();i++)
            {
                QJsonObject  chObject = jsonArray[i].toObject();

                userCourseware * pCourseware = new userCourseware;
                pCourseware->m_strCoursewareId = chObject.value("custom_course_id").toString();
                pCourseware->m_strCoursewareName = chObject.value("course_name").toString();
                pCourseware->m_strType = chObject.value("course_type").toString();
                pCourseware->m_strUrl = chObject.value("course_file").toString();
                lstUserCourseware->append(pCourseware);
            }


        }
    }
    else
    {
        qDebug()<<__FUNCTION__<<jsonError.errorString();
        return;
    }
}

void QParseInfoFromWeb::ParseStardardCaseInfo(const QByteArray &info,QList<stardardCase>* lststardardCase)
{
    if(info.isEmpty())
    {
        return;
    }
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(info,&jsonError);
    stardardCase  pCase;
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isArray())
        {
            QJsonArray jsonArray = jDoc.array();
            for (int i = 0; i < jsonArray.count();i++)
            {
                QJsonObject  chObject = jsonArray[i].toObject();
                pCase.m_strCaseId = chObject.value("m_strCaseId").toString();
                pCase.m_strName = chObject.value("m_strName").toString();
                pCase.m_strType = chObject.value("m_strType").toString();
                pCase.m_strHuman = chObject.value("m_strHuman").toString();
                pCase.m_default_sound=chObject.value("default_sound").toString();
                pCase.m_tremble=chObject.value("tremble").toString();
                QJsonArray array=chObject.value("sound_list").toArray();
                pCase.m_sound_list=QJsonDocument(array).toJson();
                lststardardCase->append(pCase);
            }
        }
    }
}

void QParseInfoFromWeb::ParseDiffSoundInfo(const QByteArray& info,QList<diffSound>* lstDiffSound)
{
    if(info.isEmpty())
    {
        return;
    }
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(info,&jsonError);
    diffSound  pCase;
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isArray())
        {

            QJsonArray jsonArray = jDoc.array();
            for (int i = 0; i < jsonArray.count();i++)
            {
                QString strType,strGroupName,strGroupId;
                QJsonObject  chObject = jsonArray[i].toObject();
                strType = chObject.value("organ_type").toString();
                strGroupName = chObject.value("discern_name").toString();
                strGroupId = chObject.value("discern_id").toString();
                QJsonValue childvalue = chObject.value("sound_list");
                if (childvalue.isArray())
                {
                    QJsonArray childjsonArray = childvalue.toArray();
                    for (int i = 0; i < childjsonArray.count();i++)
                    {
                        QJsonObject  chObject1 = childjsonArray[i].toObject();
                        pCase.m_strId = chObject1.value("case_id").toString();
                        pCase.m_strSoundName = chObject1.value("case_name").toString();
                        pCase.m_strType = strType;
                        pCase.m_strGroupName = strGroupName;
                        pCase.m_strGroupId = strGroupId;
                        lstDiffSound->append(pCase);
                    }
                }
            }
        }
    }
    else
    {
        qDebug()<<__FUNCTION__<<jsonError.errorString();
    }
}
