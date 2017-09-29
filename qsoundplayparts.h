#ifndef QSOUNDPLAYPARTS_H
#define QSOUNDPLAYPARTS_H
#include<windows.h>
#include<QString>
#include "qsoundresource.h"

//-------------------声音播放部件----------------------------

class QSoundPlayParts
{
public:
    QSoundPlayParts(bool bLeftTrack,QString strAppPath, bool bIgnoreTrack=false);
    ~QSoundPlayParts();
public:
    //初始化声音
    virtual void InitialSoundPart(HWND hWnd,  QByteArray strSoundInfo,QString &tremble_position,QString &default_sound);
    //
    virtual void InitialDiffSoundPart(HWND hWnd,  QByteArray strSoundInfo1,QByteArray strSoundInfo2);
    //听诊位置处理
    void OnAuscultatePosHandle( UINT uPos);
    void StopSimulateAuscultate();
    //返回震颤位置列表
    bool GetHeartVibrPos(/*out*/BYTE *pbytePos);
    QString GetPosString(bool bHeartSound);
protected:
    bool                                       m_bLeftTrack;
    bool                                       m_bIgnoreTrack;
    QString                                    m_strAppPath;
    QList<QSoundResource *>                    m_lstSoundResources;
     QList<QSoundResource *>                   testlst;
    int                                        m_nVibr;             //震颤功能号
   // m_ftp_manager downloadSoundFile;

 //   bool downloadFinsh;
};

#endif // QSOUNDPLAYPARTS_H
