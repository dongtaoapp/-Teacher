#include "qsoundresource.h"
#include <QDebug>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <m_ftp_manager.h>
 char str[] = ("Qt5QWindowIcon");
_SoundPort::_SoundPort()
{

}

void _SoundPort::Parse(const QJsonValue &strInfo, int nState)
{
    QJsonObject  chObject = strInfo.toObject();
    if(chObject.contains("position"))
    {
        QJsonValue value = chObject.value("position");
        if (value.isString())
        {
            m_uPos = value.toString().toUInt();
        }
    }

    if(chObject.contains("volume"))
    {
        QJsonValue value = chObject.value("volume");
        if (value.isString())
        {
            m_nVolume = value.toString().toInt();
        }
    }

    if(nState != 0)
    {
        m_bLeftPos = JudgeIsLeftPos(m_uPos);
    }
    //    qDebug()<<m_uPos<<m_nVolume;
}

bool _SoundPort::JudgeIsLeftPos(UINT nPos)
{
    int nLeftPos[17] = {26,24,25,27,28,29,30,31,32,33,36,37,38,34,39,40,41};
//    int nRightPos[] = {17,18,19,22,23,20,21,51,48,50,42,43,44,45,46,47,49};
    for(int n = 0 ; n < 17 ; n++)
    {
        if(nLeftPos[n] == nPos)
            return TRUE;
    }
    return FALSE;
}


QSoundResource::QSoundResource(HWND hWnd, QString strSoundPath):m_pFileWavStream(hWnd,str)
{
    m_strSoundPath = strSoundPath;
    m_bPlaySound     = FALSE;
    m_bHeartSound    = FALSE;

    m_nSoundTrack           = 0;
//    char str[] = ("Qt5QWindowIcon");
//    qDebug()<<__FUNCTION__<<"BBBBBBBBBBBBBBBBBBBBBBBBB";
//    m_pFileWavStream = new CHLFileWavStreamIn(hWnd,str);

//    connect()
}

QSoundResource::~QSoundResource()
{
    while (!m_lstSoundPort.isEmpty())
    {
          delete m_lstSoundPort.takeFirst();
    }
}

bool QSoundResource::InitialSoundResource(const QJsonValue& value, int nTrack, bool bDefault)
{
    m_nSoundTrack  = nTrack;
    m_bHeartSound    = FALSE;
    m_bDefault = bDefault;

    QString strFtpFilePath;

    QJsonObject  chObject = value.toObject();


    if(chObject.contains("sound_file"))
    {
        QJsonValue value = chObject.value("sound_file");
        if (value.isString())
        {
            strFtpFilePath = value.toString();
            QString strTemp = strFtpFilePath.right(4);
            if(strTemp.toLower() == ".wav")
            {
                QString strFileName =strFtpFilePath.mid(strFtpFilePath.lastIndexOf("/")+1);
               m_strFile = m_strSoundPath + "/Resource/Sounds/DefaultSound/" + strFileName;

                //Ω¯––≤•∑≈◊º±∏

                QString strTemp = m_strFile;
                strTemp.replace(QString("/"),QString("\\"));
//                qDebug()<<__FUNCTION__<<strTemp;
    if( !m_pFileWavStream.BeginWavePlay(strTemp.toLocal8Bit().data(),true,CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE,1.0f,m_nSoundTrack))
    {
        qDebug()<<__FUNCTION__<<"BeginWavePlay error";
//        return FALSE;
    }

//                if(strFileName == "login.wav")
//                {
//                    m_pFileWavStream->Play();
//                }
            }
            else
                return FALSE;
        }
    }
    //ÊòØÂê¶ÂøÉÈü≥
    if(chObject.contains("is_heart"))
    {
        QJsonValue value = chObject.value("is_heart");
        if (value.isString())
        {
            if( value.toString() == "1")
                m_bHeartSound = TRUE;
            else
                m_bHeartSound = FALSE;
        }

    }
    //Ëé∑Âèñ‰ΩçÁΩÆÈü≥Èáè
    if(chObject.contains("position_list"))
    {
        QJsonValue value = chObject.value("position_list");
        if(value.isArray())
        {
            QJsonArray jsonArray = value.toArray();
            for (int i = 0; i < jsonArray.count();i++)
            {
                QJsonValue childValue = jsonArray[i];
                _SoundPort *pNewSoundPort = new _SoundPort();
                pNewSoundPort->Parse(childValue);
                m_lstSoundPort.append(pNewSoundPort);
            }
        }
    }
    return TRUE;
}
//º¯±Ã˝’Ô…˘“Ù≥ı ºªØ
bool QSoundResource::InitialDiffSoundResource(const QJsonValue &value, int nTrack, bool bDefault, QString strFtpPath, int nState)
{
    m_nSoundTrack  = nTrack;
    m_bDefault = bDefault;

//    QJsonObject  chObject = value.toObject();

//    if(chObject.contains("sound_list"))
//    {
//        QJsonValue value = chObject.value("sound_list");
        if(value.isArray())
        {
            QJsonArray jsonArray = value.toArray();
//            qDebug()<<jsonArray.count();
            for (int i = 0; i < jsonArray.count();i++)
            {
                QJsonValue childValue = jsonArray[i];
                _SoundPort *pNewSoundPort = new _SoundPort();
                pNewSoundPort->Parse(childValue,nState);
                if(nState == 1 && pNewSoundPort->IsLeftPos())
                {
                    m_lstSoundPort.append(pNewSoundPort);
//                    qDebug()<<pNewSoundPort->m_bLeftPos<<pNewSoundPort->m_nVolume<<pNewSoundPort->m_uPos;
                }
                else if(nState == 2 && !pNewSoundPort->IsLeftPos())
                {
                    m_lstSoundPort.append(pNewSoundPort);
//                    qDebug()<<pNewSoundPort->m_bLeftPos<<pNewSoundPort->m_nVolume<<pNewSoundPort->m_uPos;
                }
            }
        }
//    }
//    else
//        return FALSE;

    QString strTemp = strFtpPath.right(4);
    if(strTemp.toLower() == ".wav")
    {
        QString strFileName =strFtpPath.mid(strFtpPath.lastIndexOf("/")+1);
        if(bDefault)
            m_strFile = m_strSoundPath + "/Resource/Sounds/DefaultSound/" + strFileName;
        else
        {
            m_strFile = m_strSoundPath + "/Resource/Sounds/UserSound/" + strFileName;
        }
        QString strTemp = m_strFile;
        strTemp.replace(QString("/"),QString("\\"));

        if( !m_pFileWavStream.BeginWavePlay(strTemp.toLocal8Bit().data(),true,bDefault ? CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE : CHLFileWavStreamIn::FMT_WAVFILE,1.0f,m_nSoundTrack))
        {
            return FALSE;
        }

//        if(strFileName == "1.wav")
//        {
//            m_pFileWavStream->Play();
//        }
    }
    else
        return FALSE;



    return TRUE;
}

void QSoundResource::PlayWaveSound(int nTrackState, UINT uPos)
{
    _SoundPort *pPort = FindSoundPort( uPos );
    if( pPort != NULL )
    {
        if( m_bPlaySound && m_pFileWavStream.GetStatus() == 1)
        {//Ê≠£Âú®Êí≠ÊîæÊ≠§‰ΩçÁΩÆÁöÑÂ£∞Èü≥
            //Êí≠ÊîæÊ≠§‰ΩçÁΩÆÁöÑÂ£∞Èü≥
            if( nTrackState != 0 )
            {
                m_pFileWavStream.SetPan( nTrackState == 1 ? -10000 : 10000 );
            }
            long lVolue = long(-1 * (1.0-pPort->m_nVolume*0.01) * 10000);
            m_pFileWavStream.SetVolume( lVolue );
            return;
        }
        else
        {
            m_bPlaySound = TRUE;
            //Êí≠ÊîæÊ≠§‰ΩçÁΩÆÁöÑÂ£∞Èü≥
            if( nTrackState != 0 )
            {
                m_pFileWavStream.SetPan( nTrackState == 1 ? -10000 : 10000 );
            }
            long lVolue = long(-1 * (1.0-pPort->m_nVolume*0.01) * 10000);
            m_pFileWavStream.SetVolume( lVolue );
            m_pFileWavStream.Play();
        }
    }
    else
    {
        StopSound();
    }
}

//bool QSoundResource::SaveVibrValue(BYTE *pbyteValue)
//{
//    bool bHaveVibr = FALSE;
//    if( m_nVibr != -1 )
//    {
//        bHaveVibr  = TRUE;
//        *pbyteValue = (BYTE)m_nVibr;
//    }
//    return bHaveVibr;
//}

QString QSoundResource::GetPosString()
{
    QString strPos;

    for (int i = 0; i < m_lstSoundPort.size(); ++i)
    {
        _SoundPort *pPort = m_lstSoundPort.at(i);
        QString strTemp;
        strTemp = QString("%1;").arg(pPort->m_uPos);
        strPos+=strTemp;
    }

    return strPos;
}

void QSoundResource::StopSound()
{
    if( m_bPlaySound )
    {
        m_pFileWavStream.CloseRead();
        QString strTemp = m_strFile;
        strTemp.replace(QString("/"),QString("\\"));
        m_pFileWavStream.BeginWavePlay( strTemp.toLocal8Bit().data(),true,m_bDefault ? CHLFileWavStreamIn::FMT_ENCRYPTWAVEFILE : CHLFileWavStreamIn::FMT_WAVFILE,1.0f,m_nSoundTrack);
    }
    m_bPlaySound = FALSE;
}

_SoundPort *QSoundResource::FindSoundPort(UINT uPos)
{
    for (int i = 0; i < m_lstSoundPort.size(); ++i)
    {
        _SoundPort *pPort = m_lstSoundPort.at(i);
        if(pPort->m_uPos == uPos)
            return pPort;
    }
    return NULL;
}

