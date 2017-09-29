#ifndef QLOUDAUSCULTATECONTROLVIR_H
#define QLOUDAUSCULTATECONTROLVIR_H
#include<Windows.h>
#include<qbytearray.h>
#include<qstring.h>

//------------------�����������������----------------------------

class QLoudAuscultateControlVir
{
public:
    QLoudAuscultateControlVir(HWND hWnd,QString strAppPath);
    ~QLoudAuscultateControlVir();
public:
    //��ʼ������
    virtual void InitialSoundPart( QByteArray strSoundInfo,QString &tremble_position,QString&default_sound) = 0;
    //��ʼ����������
    virtual void InitialDiffSoundPart( QByteArray strSoundInfo1,QByteArray strSoundInfo2) = 0;
    //����λ�ô���
    virtual void OnAuscultatePosHandle(bool bLeaf, UINT uPos) = 0;
    //������������
    virtual void StartLoudAuscultateHandle() = 0;
    virtual void StopLoudAuscultate() = 0;
public:
    bool  Get_IsEnableLoudAuscultate() { return m_bEnableLoudAuscultate; }
    bool  Get_IsLoudAuscultating() { return m_bLoudAuscultating; }
protected:
    bool      m_bEnableLoudAuscultate;    //�Ƿ�����������
    bool      m_bLoudAuscultating;        //�Ƿ�������������
    QString               m_strAppPath;
};

#endif // QLOUDAUSCULTATECONTROLVIR_H
