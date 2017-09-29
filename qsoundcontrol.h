#ifndef QSOUNDCONTROL_H
#define QSOUNDCONTROL_H

#include<windows.h>
#include<QString>
#include "qsoundplayparts.h"
#include <QMutex>
#include "qloudauscultatecontrolvir.h"

//---------------------------------声音控制类------------------------------

class QSoundControl
{
public:
    QSoundControl(HWND hWnd,QString strAppPath,bool bSimpleAuscultate = TRUE, bool bSimpleLoud = TRUE, BOOL bSinglePlayPart=FALSE);
    ~QSoundControl();
protected:
    bool                         m_bInitial; //是否初始化
    HWND                         m_hWnd;
    QSoundPlayParts             *m_pSoundPlayParts[2];
    QLoudAuscultateControlVir   *m_pLoudAuscultate;
private:
    QString                      m_strAppPath;
    bool                         m_bSinglePlayPart;           //是否单独的声音控制
    bool                         m_bEnableSimulateAuscultate; //是否允许模拟听诊
    bool                         m_bSimpleAuscultateMode;     //是否为简单听诊模式
    QMutex                       m_cMutex;
protected:
    void SetLoudAuscultateSound(QByteArray strSoundInfo,QString &tremble_position,QString&default_sound);
    void SetDiffLoudAuscultateSound(QByteArray strInfo1,QByteArray strInfo2);
public:
    //加载声音配置信息
    void LoadSoundConfigue(QByteArray strSoundInfo,QString &tremble_position,QString &default_sound) ;
    //
    void LoadDiffSoundConfigue(QByteArray strSoundInfo1,QByteArray strSoundInfo2);
    //听诊位置处理
    void OnAuscultatePosHandle(bool bLeaf, UINT uPos);
    //模拟听诊
    void OnSimulateAuscultateHandle();
    //停止模拟听诊
    void OnStopSimulateAusculate();
    //扩音听诊
    void OnLoudAuscultateHandle();
    //停止扩音听诊
    void OnStopLoudAuscultate();
    //返回是否能进行模拟听诊
    bool IsCanSimulateAuscultate();
    //返回是否能扩音听诊
    BOOL IsCanLoudAuscultate();
    //返回震颤位置值
    bool GetHeartVibrPosValue(/*out*/BYTE *pbytePos);
    QString GetPosString(BOOL bHeartSound);

    void CheckSoundFileDown(QByteArray &array);
};

#endif // QSOUNDCONTROL_H
