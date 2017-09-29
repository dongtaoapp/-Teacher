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
    CHLFileWavStreamIn   m_pLoudAuscultate;  //��������
    CHLFileWavStreamIn   m_pUserDefineLoudAuscultate;  //�û��Զ�����������
    QString               m_strLoudAuscultateFileName;
    bool                  m_bDefault;   //�Ƿ�ϵͳĬ��
    HWND                  hCurWnd;
    bool                  m_bDefaultNow;//��ǰ���ص������Ƿ�ΪϵͳĬ��
};

#endif // QLOUDAUSCULTATEGENERALCONTROL_H
