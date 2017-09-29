#ifndef QLOUDAUSCULTATETOUCHCONTROL_H
#define QLOUDAUSCULTATETOUCHCONTROL_H
#include "qloudauscultatecontrolvir.h"
#include "qloudauscultatetouchplayparts.h"

class QLoudAuscultateTouchControl : public QLoudAuscultateControlVir
{
public:
    QLoudAuscultateTouchControl(HWND hWnd,QString strAppPath,bool bSinglePlayPart = FALSE);
    ~QLoudAuscultateTouchControl();
public:
    //初始化声音
    virtual void InitialSoundPart( QByteArray strSoundInfo,QString &tremble_position,QString &default_sound);
    //初始化鉴别听诊
    virtual void InitialDiffSoundPart( QByteArray strSoundInfo1,QByteArray strSoundInfo2);
    //听诊位置处理
    virtual void OnAuscultatePosHandle(bool bLeaf, UINT uPos);
    //启动扩音听诊
    virtual void StartLoudAuscultateHandle();
    //停止扩音听诊
    virtual void StopLoudAuscultate();
protected:
    QLoudAuscultateTouchPlayParts*  m_pSoundPlayParts[2];
    HWND                            m_hWnd;
    bool                            m_bSinglePlayPart;

};

#endif // QLOUDAUSCULTATETOUCHCONTROL_H
