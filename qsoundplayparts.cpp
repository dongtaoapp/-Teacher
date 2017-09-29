#include "qsoundplayparts.h"
#include "define.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
QSoundPlayParts::QSoundPlayParts(bool bLeftTrack, QString strAppPath, bool bIgnoreTrack)
{
    m_bLeftTrack       = bLeftTrack;
    m_bIgnoreTrack     = bIgnoreTrack;
    m_strAppPath = strAppPath;
    m_nVibr          = -1;
    //downloadFinsh=true;
    //downloadInit();

}
QSoundPlayParts::~QSoundPlayParts()
{
    while (!m_lstSoundResources.isEmpty())
          delete m_lstSoundResources.takeFirst();
    qDebug()<<__FUNCTION__;
}

void QSoundPlayParts::InitialSoundPart(HWND hWnd,  QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
    while (!m_lstSoundResources.isEmpty())
    {
          delete m_lstSoundResources.takeFirst();
    }
    m_nVibr          = -1;
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(strSoundInfo,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
        {

            if (jDoc.isArray())
            {
//                QString strSoundPath;
                QString strDefaultSound;
                bool bDefault;

             //   QJsonObject rootObj = jDoc.object();

/*                if (rootObj.contains("is_default"))
                {
                    QJsonValue value = rootObj.value("is_default");

                    if (value.isString())
                    {
                        //鍒ゆ柇鏄惁鏄粯璁よ浠
                        if(value.toString() == "1")
                            bDefault = TRUE;
//                            strSoundPath = m_strAppPath + "/Resource/Sounds/DefaultSound/";
                        else
                            bDefault = FALSE;
//                            strSoundPath = m_strAppPath + "/Resource/Sounds/UserSound/";
//                        qDebug()<<strSoundPath;
                    }
                }*/
                bDefault = TRUE;
                //鑾峰彇闇囬ⅳ鍙
//                if (rootObj.contains("tremble_position"))
//                {
//                    QJsonValue value = rootObj.value("tremble_position");

//                    if (value.isString())
//                    {
//                        m_nVibr = value.toString().toInt();
//                    }
//                }
                m_nVibr=tremble_position.toInt();
                //鑾峰彇鎵╅煶鍚瘖闊
//                if (rootObj.contains("default_sound"))
//                {
//                    QJsonValue value = rootObj.value("default_sound");

//                    if (value.isString())
//                    {
//                        strDefaultSound = value.toString();
//                    }
//                }
                strDefaultSound=default_sound;
                //鑾峰彇澹伴煶鍒楄〃
              //  if (rootObj.contains("sound_list"))
                //{
                //    qDebug()<<__FUNCTION__<<"ndjafsnadsjlkgnblajkfndsbgjlabfgjkbajfgabjkgbjabfdajlkgjblkajgal";
             //       QJsonValue value = rootObj.value("sound_list");

                //    if (value.isArray())
                 //   {
                        QJsonArray jsonArray =jDoc.array();
                        for (int i = 0; i < jsonArray.count();i++)
                        {
                            QJsonValue childValue = jsonArray[i];

                            QSoundResource *pNewResource = new QSoundResource(hWnd,m_strAppPath);
                             m_lstSoundResources.append(pNewResource);
                            testlst.append(pNewResource);
                            int  nTrack = 0;
                            if( !m_bIgnoreTrack )
                            {
                                nTrack = m_bLeftTrack ? 1 : 2;
                            }
                            //bDefault jiami
                            if( pNewResource->InitialSoundResource( childValue, nTrack,bDefault) )
                            {
//                                m_lstSoundResources.append(pNewResource);
//                                qDebug()<<"strSoundPath";
                            }
                            else
                            {
                                delete pNewResource;
                            }
                        }
                 //   }
              //   }
            }
        }
    else
    {
        qDebug()<<__FUNCTION__<<jsonError.errorString()<<"+++++++++++++++++++++++++++++++++++++";
    }
}


void QSoundPlayParts::InitialDiffSoundPart(HWND hWnd,  QByteArray strSoundInfo1,QByteArray strSoundInfo2)
{
    while (!m_lstSoundResources.isEmpty())
          delete m_lstSoundResources.takeFirst();
    m_nVibr          = -1;

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

            //鑾峰彇澹伴煶鍒楄〃
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

                        if( pNewResource->InitialDiffSoundResource( value, nTrack,bDefault,strFtpPath,(bHeart ? 0 : 1)) )
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
    else
    {
        qDebug()<<__FUNCTION__<<"DiffSoundFile0 Json error";
        return;
    }

    //parse rightsound
    if(!strSoundInfo2.isEmpty())
    {
        jDoc = QJsonDocument::fromJson(strSoundInfo2,&jsonError);
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

                //鑾峰彇澹伴煶鍒楄〃
                if (rootObj.contains("sound_list"))
                {
                    QJsonValue value = rootObj.value("sound_list");

//                    if (value.isArray())
//                    {
//                        QJsonArray jsonArray = value.toArray();
//                        for (int i = 0; i < jsonArray.count();i++)
//                        {
//                            QJsonValue childValue = jsonArray[i];

                            QSoundResource *pNewResource = new QSoundResource(hWnd,m_strAppPath);
                            int  nTrack = 0;
                            if( !m_bIgnoreTrack )
                            {
                                nTrack = m_bLeftTrack ? 1 : 2;
                            }

                            if( pNewResource->InitialDiffSoundResource( value, nTrack,bDefault,strFtpPath,2) )
                            {
                                m_lstSoundResources.append(pNewResource);
    //                                qDebug()<<"strSoundPath";
                            }
                            else
                            {
                                delete pNewResource;
                            }
//                        }
//                    }
                 }

            }
            else
            {
                qDebug()<<__FUNCTION__<<"DiffSoundFile1 Json error";
                return;
            }
        }

    }
}

void QSoundPlayParts::OnAuscultatePosHandle(UINT uPos)
{

    //鎾斁姝や綅缃笂鐨勫０闊
    for (int i = 0; i < m_lstSoundResources.size(); ++i)
    {
          QSoundResource *pSoundResource = m_lstSoundResources.at(i);
          int nTrackState = 0;
          if( !m_bIgnoreTrack )
          {
             //澹伴亾鐘舵€侊細-1锛氬彸澹伴亾锛锛氫笉鍒嗗乏鍙冲０閬擄紱1:宸﹀０閬
             nTrackState = m_bLeftTrack ? 1 : -1;
          }
          pSoundResource->PlayWaveSound(nTrackState, uPos);
    }


}

void QSoundPlayParts::StopSimulateAuscultate()
{
    //鍏抽棴鎵€鏈夋挱鏀剧殑澹伴煶
    for (int i = 0; i < m_lstSoundResources.size(); ++i)
    {
          QSoundResource *pSoundResource = m_lstSoundResources.at(i);
          int nTrackState = 0;
          if( !m_bIgnoreTrack )
          {
             //澹伴亾鐘舵€侊細-1锛氬彸澹伴亾锛锛氫笉鍒嗗乏鍙冲０閬擄紱1:宸﹀０閬
             nTrackState = m_bLeftTrack ? 1 : -1;
          }
          pSoundResource->PlayWaveSound(nTrackState, -1);
    }
}

bool QSoundPlayParts::GetHeartVibrPos(BYTE *pbytePos)
{
    bool bHaveVibr = FALSE;
    if( m_nVibr != -1 )
    {
        bHaveVibr  = TRUE;
        *pbytePos = (BYTE)m_nVibr;
    }
    return bHaveVibr;
}

QString QSoundPlayParts::GetPosString(bool bHeartSound)
{
    QString strPos="";

    for (int i = 0; i < m_lstSoundResources.size(); ++i)
    {
          QSoundResource *pRes = m_lstSoundResources.at(i);
          if( pRes->IsHeartSoundResource() == bHeartSound )
          {
              QString strTemp;
              strTemp = pRes->GetPosString();
              strPos += strTemp;
          }

    }

    return strPos;
}
