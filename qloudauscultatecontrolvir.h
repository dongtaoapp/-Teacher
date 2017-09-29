#ifndef QLOUDAUSCULTATECONTROLVIR_H
#define QLOUDAUSCULTATECONTROLVIR_H
#include<Windows.h>
#include<qbytearray.h>
#include<qstring.h>

//------------------扩音听诊基础控制类----------------------------

class QLoudAuscultateControlVir
{
public:
    QLoudAuscultateControlVir(HWND hWnd,QString strAppPath);
    ~QLoudAuscultateControlVir();
public:
    //初始化声音
    virtual void InitialSoundPart( QByteArray strSoundInfo,QString &tremble_position,QString&default_sound) = 0;
    //初始化鉴别听诊
    virtual void InitialDiffSoundPart( QByteArray strSoundInfo1,QByteArray strSoundInfo2) = 0;
    //听诊位置处理
    virtual void OnAuscultatePosHandle(bool bLeaf, UINT uPos) = 0;
    //启动扩音听诊
    virtual void StartLoudAuscultateHandle() = 0;
    virtual void StopLoudAuscultate() = 0;
public:
    bool  Get_IsEnableLoudAuscultate() { return m_bEnableLoudAuscultate; }
    bool  Get_IsLoudAuscultating() { return m_bLoudAuscultating; }
protected:
    bool      m_bEnableLoudAuscultate;    //是否能扩音听诊
    bool      m_bLoudAuscultating;        //是否正在扩音听诊
    QString               m_strAppPath;
};

#endif // QLOUDAUSCULTATECONTROLVIR_H
