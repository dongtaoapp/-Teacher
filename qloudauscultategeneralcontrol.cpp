#include "qloudauscultategeneralcontrol.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
extern char str[] ;
QLoudAuscultateGeneralControl::QLoudAuscultateGeneralControl(HWND hWnd,QString strAppPath):QLoudAuscultateControlVir(hWnd,strAppPath)
  ,m_pLoudAuscultate(hWnd,str),m_pUserDefineLoudAuscultate(hWnd,str)
{
    hCurWnd = hWnd;

//    m_pLoudAuscultate = new CHLFileWavStreamIn(hWnd,str);
//    m_pUserDefineLoudAuscultate = new CHLFileWavStreamIn(hWnd,str);

//    QString s = "G:\\Test\\project\\QtSelectCourseware\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";
//    QString s = "H:\\PhysicalCheck\\Train-teacher\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";
//    char str1[] = ("Qt5QWindowIcon");
//    QByteArray bLocal = s.toLocal8Bit();
//////    qDebug() << s;
//    CHLFileWavStreamIn   *f = new CHLFileWavStreamIn(hWnd,str);
////    m_pLoudAuscultate = f;
//    if(f->BeginWavePlay(bLocal.data(),true,TRUE ? CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE : CHLFileWavStreamIn::FMT_WAVFILE))
//    {
//       qDebug()<<"qt";
//    }
//    else
//    {
//        qDebug()<<"qt error";
//    }

//    f->Play();
}

QLoudAuscultateGeneralControl::~QLoudAuscultateGeneralControl()
{
//    if(m_pLoudAuscultate != NULL)
//        delete m_pLoudAuscultate;
//    if(m_pUserDefineLoudAuscultate != NULL)
//        delete m_pUserDefineLoudAuscultate;
}
//-----------------简易扩音听诊
void QLoudAuscultateGeneralControl::InitialSoundPart( QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
//    m_pLoudAuscultate->Play();

    if(m_bEnableLoudAuscultate /*&& m_pLoudAuscultate != NULL*/)
    {
        if(m_bDefaultNow )
            m_pLoudAuscultate.CloseRead();
        else if(!m_bDefaultNow)
            m_pUserDefineLoudAuscultate.CloseRead();
        m_bEnableLoudAuscultate = FALSE;
    }

//    QJsonDocument jDoc;
//    QJsonParseError jsonError;
//    jDoc = QJsonDocument::fromJson(strSoundInfo,&jsonError);
//    if (jsonError.error == QJsonParseError::NoError)
//    {
//        if (jDoc.isObject())
//        {
//            bool bDefault;
            QString strDefaultSound;

//            QJsonObject rootObj = jDoc.object();

//            if (rootObj.contains("is_default"))
//            {
//                QJsonValue value = rootObj.value("is_default");

//                if (value.isString())
//                {
//                    if(value.toString() == "1")
//                        m_bDefault = TRUE;
//                    else
//                        m_bDefault = FALSE;
//                }
//            }
               m_bDefault = TRUE;
//            if (rootObj.contains("default_sound"))
//            {
//                QJsonValue value = rootObj.value("default_sound");

//                if (value.isString())
//                {
                    QString strTemp11;
                    strTemp11 = default_sound;
                    strDefaultSound = strTemp11.mid(strTemp11.lastIndexOf("/")+1);
//                    qDebug()<<strDefaultSound;
                    strDefaultSound = QString(QStringLiteral("%1")).arg(strDefaultSound);
//                    char* p[] = strDefaultSound.toLocal8Bit().data();
//                    strDefaultSound = QStringLiteral(p);
              //  }
//            }

            if(m_bDefault == TRUE)
                m_strLoudAuscultateFileName = m_strAppPath + "/Resource/Sounds/DefaultSound/" + strDefaultSound;
//            else
//            {
//                m_strLoudAuscultateFileName = m_strAppPath + "/Resource/Sounds/UserSound/" + strDefaultSound;
//                //本地是否有文件
//                QFile f(m_strLoudAuscultateFileName);
//                if(!f.exists())
//                    //扩音听诊=================================================
//                {
//                    //.....下载ftp文件(未完成)

////                        qDebug()<<m_strFile;
//                }
//            }

            QString strTemp = m_strLoudAuscultateFileName;
            strTemp.replace(QString("/"),QString("\\"));

//            strTemp = "H:\\PhysicalCheck\\Train-teacher\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";

//            strTemp = "G:\\Test\\project\\QtSelectCourseware\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";
//            qDebug()<<strTemp;

//            if( m_pLoudAuscultate->BeginWavePlay(strTemp.toLocal8Bit().data(),true,m_bDefault ? CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE : CHLFileWavStreamIn::FMT_WAVFILE))
//            {
//                m_bEnableLoudAuscultate = TRUE;
////                m_pLoudAuscultate->Play();
//            }




            if(m_bDefault == TRUE)
            {
                if( m_pLoudAuscultate.BeginWavePlay(strTemp.toLocal8Bit().data(),true,CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE ))
                {
                    m_bEnableLoudAuscultate = TRUE;
                    m_bDefaultNow = TRUE;
    //                m_pLoudAuscultate->Play();
                }
                else
                {
                }
            }
//            else
//            {
//                if( m_pUserDefineLoudAuscultate->BeginWavePlay(strTemp.toLocal8Bit().data(),true,CHLFileWavStreamIn::FMT_WAVFILE ))
//                {
//                    m_bEnableLoudAuscultate = TRUE;
//                    m_bDefaultNow = FALSE;
//    //                m_pLoudAuscultate->Play();
//                }
//            }





//        }

}

void QLoudAuscultateGeneralControl::InitialDiffSoundPart(QByteArray strSoundInfo1, QByteArray strSoundInfo2)
{
//    if(m_bEnableLoudAuscultate && m_pLoudAuscultate != NULL)
//    {
//        m_pLoudAuscultate->CloseRead();

//        m_bEnableLoudAuscultate = FALSE;
//    }


    if(m_bEnableLoudAuscultate /*&& m_pLoudAuscultate != NULL*/)
    {
        if(m_bDefaultNow)
            m_pLoudAuscultate.CloseRead();
        else if(!m_bDefaultNow )
            m_pUserDefineLoudAuscultate.CloseRead();
        m_bEnableLoudAuscultate = FALSE;
    }

    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(strSoundInfo1,&jsonError);
    if (jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isObject())
        {
            QString strDefaultSound;

            QJsonObject rootObj = jDoc.object();

            if (rootObj.contains("system_custom"))
            {
                QJsonValue value = rootObj.value("system_custom");

                if (value.isString())
                {
                    if(value.toString() == "0")
                        m_bDefault = TRUE;
                    else
                        m_bDefault = FALSE;
                }
            }

            if (rootObj.contains("sound_file"))
            {
                QJsonValue value = rootObj.value("sound_file");

                if (value.isString())
                {
                    QString strTemp;
                    strTemp = value.toString();
                    strDefaultSound = strTemp.mid(strTemp.lastIndexOf("/")+1);
//                    qDebug()<<strDefaultSound;
                    strDefaultSound = QString(QStringLiteral("%1")).arg(strDefaultSound);
//                    char* p[] = strDefaultSound.toLocal8Bit().data();
//                    strDefaultSound = QStringLiteral(p);
                }
            }

            if(m_bDefault == TRUE)
                m_strLoudAuscultateFileName = m_strAppPath + "/Resource/Sounds/DefaultSound/" + strDefaultSound;
            else
            {
                m_strLoudAuscultateFileName = m_strAppPath + "/Resource/Sounds/UserSound/" + strDefaultSound;
                //本地是否有文件
                QFile f(m_strLoudAuscultateFileName);
                if(!f.exists())
                {
                    //.....下载ftp文件(未完成)
//                        qDebug()<<m_strFile;
                }
            }

            QString strTemp = m_strLoudAuscultateFileName;
            strTemp.replace(QString("/"),QString("\\"));

//            strTemp = "H:\\PhysicalCheck\\Train-teacher\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";

//            strTemp = "G:\\Test\\project\\QtSelectCourseware\\debug\\Resource\\Sounds\\DefaultSound\\1.wav";
//            qDebug()<<strTemp;


//            if( m_pLoudAuscultate->BeginWavePlay(strTemp.toLocal8Bit().data(),true,m_bDefault ? CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE : CHLFileWavStreamIn::FMT_WAVFILE))
//            {
//                m_bEnableLoudAuscultate = TRUE;
////                m_pLoudAuscultate->Play();
//            }


//            if(strDefaultSound == "1.wav")
//            {
//                m_pLoudAuscultate->Play();
//            }


            if(m_bDefault == TRUE)
            {
                if( m_pLoudAuscultate.BeginWavePlay(strTemp.toLocal8Bit().data(),true,CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE ))
                {
                    m_bEnableLoudAuscultate = TRUE;
                    m_bDefaultNow = TRUE;
//                    m_pLoudAuscultate->Play();
                }
            }
            else
            {
                if( m_pUserDefineLoudAuscultate.BeginWavePlay(strTemp.toLocal8Bit().data(),true,CHLFileWavStreamIn::FMT_WAVFILE ))
                {
                    m_bEnableLoudAuscultate = TRUE;
                    m_bDefaultNow = FALSE;
//                    m_pUserDefineLoudAuscultate->Play();
                }
            }


        }
    }



}

void QLoudAuscultateGeneralControl::OnAuscultatePosHandle(bool bLeaf, UINT uPos)
{

}

void QLoudAuscultateGeneralControl::StartLoudAuscultateHandle()
{
//    if(m_bEnableLoudAuscultate && m_pLoudAuscultate->GetStatus() != 1)
//    {
//        m_pLoudAuscultate->Play();
//        m_bLoudAuscultating = TRUE;
//    }

    if(m_bEnableLoudAuscultate /*&& m_pLoudAuscultate->GetStatus() != 1*/)
    {
        if(m_bDefaultNow)
        {
            if(m_pLoudAuscultate.GetStatus() != 1)
            {
                m_pLoudAuscultate.Play();
                m_bLoudAuscultating = TRUE;
            }
        }
        else
        {
            if(m_pUserDefineLoudAuscultate.GetStatus() != 1)
            {

                m_pUserDefineLoudAuscultate.Play();
                m_bLoudAuscultating = TRUE;
            }
        }

    }
}

void QLoudAuscultateGeneralControl::StopLoudAuscultate()
{
    if(m_bDefaultNow)
    {
        if(m_pLoudAuscultate.GetStatus() == 1)
        {//播放状态
            m_pLoudAuscultate.CloseRead();

            QString strTemp = m_strLoudAuscultateFileName;
            strTemp.replace(QString("/"),QString("\\"));
            if( m_pLoudAuscultate.BeginWavePlay(strTemp.toLocal8Bit().data(),true, CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE ))
            {
                m_bEnableLoudAuscultate = TRUE;
                return;
            }
    //        else
    //        {
    //            m_bEnableLoudAuscultate = FALSE;
    //        }
        }
    }
    else
    {
        if(m_pUserDefineLoudAuscultate.GetStatus() == 1)
        {//播放状态
            m_pUserDefineLoudAuscultate.CloseRead();

            QString strTemp = m_strLoudAuscultateFileName;
            strTemp.replace(QString("/"),QString("\\"));
            if( m_pUserDefineLoudAuscultate.BeginWavePlay(strTemp.toLocal8Bit().data(),true, CHLFileWavStreamIn::FMT_WAVFILE))
            {
                m_bEnableLoudAuscultate = TRUE;
                return;
            }
    //        else
    //        {
    //            m_bEnableLoudAuscultate = FALSE;
    //        }
        }
    }


    m_bLoudAuscultating  = FALSE;
}
