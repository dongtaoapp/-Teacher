#ifndef QSOUNDRESOURCE_H
#define QSOUNDRESOURCE_H

#include<windows.h>
#include<QString>
#include <QVariant>

extern "C"
{
#include "PlayWavDll.h"
}

//--------------------声音资源类--------------------


struct _SoundPort
{
    UINT        m_uPos;
    int         m_nVolume;
    bool        m_bLeftPos;
public:
    _SoundPort();
public:
    void Parse(const QJsonValue& strInfo,int nState = 0);
    bool JudgeIsLeftPos(UINT nPos);
    bool IsLeftPos() { return m_bLeftPos; }
};

Q_DECLARE_METATYPE(_SoundPort);

class QSoundResource
{
public:
    QSoundResource(HWND hWnd,QString strSoundPath);
    ~QSoundResource();
public:
    bool InitialSoundResource(const QJsonValue& value, int nTrack,bool bDefault);
    //state: 0:noside,1:left,2:right
    bool InitialDiffSoundResource(const QJsonValue& value, int nTrack,bool bDefault,QString strFtpPath,int nState = 0);
    void PlayWaveSound(int nTrackState, UINT uPos);
//    bool SaveVibrValue(BYTE *pbyteValue);
    //返回是否为心音听诊
    bool IsHeartSoundResource() { return m_bHeartSound; }
    QString GetPosString(void);

signals:
    void downFile();
protected:
    //停止声音的播放
    void StopSound();
    //判断在指定的端口上所有需要播放此声音
    _SoundPort * FindSoundPort(UINT uPos);
protected:
    QString                           m_strSoundPath;
    CHLFileWavStreamIn                m_pFileWavStream;
    bool                              m_bHeartSound;
    QList<_SoundPort *>               m_lstSoundPort;
    QString                           m_strFile;
    bool                              m_bPlaySound;        //正在播放声音
    int                               m_nSoundTrack;       //声道控制；0：不控制；1：左声道；2：右声道
    bool                              m_bDefault;           //
};

#endif // QSOUNDRESOURCE_H
