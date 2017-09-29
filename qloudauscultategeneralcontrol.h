#ifndef QLOUDAUSCULTATEGENERALCONTROL_H
#define QLOUDAUSCULTATEGENERALCONTROL_H
#include "qloudauscultatecontrolvir.h"
extern "C"
{
#include "PlayWavDll.h"
}


class QLoudAuscultateGeneralControl : public QLoudAuscultateControlVir
{
public:
    QLoudAuscultateGeneralControl(HWND hWnd,QString strAppPath);
    ~QLoudAuscultateGeneralControl();
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
    CHLFileWavStreamIn   m_pLoudAuscultate;  //扩音听诊
    CHLFileWavStreamIn   m_pUserDefineLoudAuscultate;  //用户自定义扩音听诊
    QString               m_strLoudAuscultateFileName;
    bool                  m_bDefault;   //是否系统默认
    HWND                  hCurWnd;
    bool                  m_bDefaultNow;//当前加载的声音是否为系统默认
};

#endif // QLOUDAUSCULTATEGENERALCONTROL_H
