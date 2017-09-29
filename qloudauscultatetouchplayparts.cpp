#include "qloudauscultatetouchplayparts.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QLoudAuscultateTouchPlayParts::QLoudAuscultateTouchPlayParts(bool bLeftTrack, QString strAppPath, bool bIgnoreTrack):QSoundPlayParts(bLeftTrack,strAppPath,bIgnoreTrack)
{

}

void QLoudAuscultateTouchPlayParts::InitialSoundPart(HWND hWnd, QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
    while (!m_lstSoundResources.isEmpty())
          delete m_lstSoundResources.takeFirst();
    QString strDefaultSound;
    bool bDefault;

    bDefault = TRUE;
    strDefaultSound=default_sound;
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(strSoundInfo,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
      /*
        if (jDoc.isObject())
        {

            QJsonObject rootObj = jDoc.object();
            //是否系统默认
            if (rootObj.contains("is_default"))
            {
                QJsonValue value = rootObj.value("is_default");

                if (value.isString())
                {
                    //判断是否是默认课件
                    if(value.toString() == "1")
                            strSoundPath = m_strAppPath + "/Resource/Sounds/DefaultSound/";
                    else
                        bDefault = FALSE;
                            strSoundPath = m_strAppPath + "/Resource/Sounds/UserSound/";
                }

            获取扩音听诊音
            if (rootObj.contains("default_sound"))
            {
                QJsonValue value = rootObj.value("default_sound");

                if (value.isString())
                {
                    strDefaultSound = value.toString();
                }
            }
            */
            //获取声音列表
            if (jDoc.isArray())
            {
//                QJsonValue value = rootObj.value("sound_list");

//                if (value.isArray())
//                {
                    QJsonArray jsonArray = jDoc.array();
                    for (int i = 0; i < jsonArray.count();i++)
                    {
                        QJsonValue childValue = jsonArray[i];
                        if(ReturnSoundName(childValue) == strDefaultSound)
                        {
                            QSoundResource *pNewResource = new QSoundResource(hWnd,m_strAppPath);
                             m_lstSoundResources.append(pNewResource);
                            int  nTrack = 0;
                            if( !m_bIgnoreTrack )
                            {
                                nTrack = m_bLeftTrack ? 1 : 2;
                            }
                            if( pNewResource->InitialSoundResource( childValue, nTrack,bDefault) )
                            {
//                                m_lstSoundResources.append(pNewResource);
//                                qDebug()<<"strSoundPath";
                            }
                            else
                            {
                                delete pNewResource;
                            }
                            break;
                        }

                    }
//                }

            }




    }
}

void QLoudAuscultateTouchPlayParts::InitialDiffSoundPart(HWND hWnd, QByteArray strSoundInfo1, QByteArray strSoundInfo2)
{
    while (!m_lstSoundResources.isEmpty())
          delete m_lstSoundResources.takeFirst();
//    m_nVibr          = -1;

    //是否心音
    bool bHeart;
    if(strSoundInfo2.isEmpty())
        bHeart = TRUE;
    else
        bHeart = FALSE;

    //parse heartsound or left lungsound
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(strSoundInfo1,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isObject())
        {
            QString strFtpPath;
            bool bDefault;

            QJsonObject rootObj = jDoc.object();
            //
            strFtpPath = rootObj.value("sound_file").toString();

            if(rootObj.value("system_custom").toString() == "0")
                bDefault = TRUE;
            else
                bDefault = FALSE;

            //获取声音列表
            if (rootObj.contains("sound_list"))
            {
                QJsonValue value = rootObj.value("sound_list");

//                if (value.isArray())
//                {
//                    QJsonArray jsonArray = value.toArray();
//                    for (int i = 0; i < jsonArray.count();i++)
//                    {
//                        QJsonValue childValue = jsonArray[i];

                        QSoundResource *pNewResource = new QSoundResource(hWnd,m_strAppPath);
                        int  nTrack = 0;
                        if( !m_bIgnoreTrack )
                        {
                            nTrack = m_bLeftTrack ? 1 : 2;
                        }

                        if( pNewResource->InitialDiffSoundResource( value, nTrack,bDefault,strFtpPath) )
                        {
                            m_lstSoundResources.append(pNewResource);
//                                qDebug()<<"strSoundPath";
                        }
                        else
                        {
                            delete pNewResource;
                        }
//                    }
//                }
             }
        }
    }

//    //parse rightsound
//    if(!strSoundInfo2.isEmpty())
//    {
//        jDoc = QJsonDocument::fromJson(strSoundInfo1,&jsonError);
//        if (jsonError.error == QJsonParseError::NoError)
//        {
//            if (jDoc.isObject())
//            {
//                QString strFtpPath;
//                bool bDefault;

//                QJsonObject rootObj = jDoc.object();
//                //
//                strFtpPath = rootObj.value("sound_file").toString();

//                if(rootObj.value("system_custom").toString() == "0")
//                    bDefault = TRUE;
//                else
//                    bDefault = FALSE;

//                //获取声音列表
//                if (rootObj.contains("sound_list"))
//                {
//                    QJsonValue value = rootObj.value("sound_list");

//                    if (value.isArray())
//                    {
//                        QJsonArray jsonArray = value.toArray();
//                        for (int i = 0; i < jsonArray.count();i++)
//                        {
//                            QJsonValue childValue = jsonArray[i];

//                            QSoundResource *pNewResource = new QSoundResource(hWnd,m_strAppPath);
//                            int  nTrack = 0;
//                            if( !m_bIgnoreTrack )
//                            {
//                                nTrack = m_bLeftTrack ? 1 : 2;
//                            }

//                            if( pNewResource->InitialDiffSoundResource( childValue, nTrack,bDefault,strFtpPath,2) )
//                            {
//                                m_lstSoundResources.append(pNewResource);
//    //                                qDebug()<<"strSoundPath";
//                            }
//                            else
//                            {
//                                delete pNewResource;
//                            }
//                        }
//                    }
//                 }

//            }
//        }
//    }
}



bool QLoudAuscultateTouchPlayParts::InitialLoadLoudSound(HWND hWnd, QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
    InitialSoundPart(hWnd,strSoundInfo,tremble_position,default_sound);
    return (m_lstSoundResources.size() != 0) ? TRUE : FALSE;
}

bool QLoudAuscultateTouchPlayParts::InitialLoadDiffLoudSound(HWND hWnd, QByteArray strSoundInfo1, QByteArray strSoundInfo2)
{
    InitialDiffSoundPart(hWnd,strSoundInfo1,strSoundInfo2);
    return (m_lstSoundResources.size() != 0) ? TRUE : FALSE;
}


QString QLoudAuscultateTouchPlayParts::ReturnSoundName(const QJsonValue& value)
{
    QString strFilePath;

    QJsonObject  chObject = value.toObject();


    if(chObject.contains("sound_file"))
    {
        QJsonValue value = chObject.value("sound_file");
                   //判断是否是string类型
        if (value.isString())
        {
            strFilePath = value.toString();
        }
    }
    return strFilePath;
}
