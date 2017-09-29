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
    //��ʼ������
    virtual void InitialSoundPart( QByteArray strSoundInfo,QString &tremble_position,QString &default_sound);
    //��ʼ����������
    virtual void InitialDiffSoundPart( QByteArray strSoundInfo1,QByteArray strSoundInfo2);
    //����λ�ô���
    virtual void OnAuscultatePosHandle(bool bLeaf, UINT uPos);
    //������������
    virtual void StartLoudAuscultateHandle();
    //ֹͣ��������
    virtual void StopLoudAuscultate();
protected:
    QLoudAuscultateTouchPlayParts*  m_pSoundPlayParts[2];
    HWND                            m_hWnd;
    bool                            m_bSinglePlayPart;

};

#endif // QLOUDAUSCULTATETOUCHCONTROL_H
