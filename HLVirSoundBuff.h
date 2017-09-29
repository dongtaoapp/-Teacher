// HLVirSoundBuff.h: interface for the CHLVirSoundBuff class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_HLVIRSOUNDBUFF_H__975B625E_5C88_471C_8870_2531DDBDD2BA__INCLUDED_)
//#define AFX_HLVIRSOUNDBUFF_H__975B625E_5C88_471C_8870_2531DDBDD2BA__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include <mmsystem.h>
#include <mmreg.h>

//#include <afxmt.h>
#include "HLWavStreamOut.h"
#include "HLLoopBuff.h"

#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif

//------------------------------------------------------------------------------
//   ��Ĺ��ܣ���Ƶ����Դ�Ļ��ࣻ�Ǵ����ࡣ��Ƶ����Դ����WAV�ļ������紫��������õ���
//             �������߼����ǻ��ε��ڴ滺��������Ϊ��CHLWavStreamOut������Դ.
//--------------------------------------------------------------------------------
#define DSSPEAKER_WIDE   0  //The speakers are directed over an arc of 20 degrees
#define DSSPEAKER_NARROW 1  //The speakers are directed over an arc of 10 degrees
#define DSSPEAKER_MIN    2  //The speakers are directed over an arc of 5 degrees
#define DSSPEAKER_MAX    3  //The speakers are directed over an arc of 180 degrees.

class CHLWavStreamOut;
//class CHLDisplayWaveStatic;
class CLASS_EXPORT CHLVirSoundBuff /*: public CObject */ 
{
	friend CHLWavStreamOut;
public:
	CHLWavStreamOut *m_pWavStreamOut;
	HWND            m_hWnd; //���ھ��
public:
	CHLVirSoundBuff(HWND hWnd);
	virtual ~CHLVirSoundBuff();
public:
	//CCriticalSection m_Section2;
	CRITICAL_SECTION gSection;
	HANDLE           m_hThreadOutEvent;   //�߳��˳��¼�
protected:
	HANDLE   m_hEventFinish; //�����̵߳Ľ���
protected:
	bool Initialize(WAVEFORMATEX *pLesserFormat,UINT umillisecond = 4000);

	LPDIRECTSOUND m_pDirectSound; //DirectSound����

	UINT m_nNotifyNum; //DSBPOSITIONNOTIFY�ṹ������Ԫ�صĸ���
	//DSBPOSITIONNOTIFY�ṹ���飬ÿһ���벶�񻺳�������ϵ���¼�����Ҫһ����
	//����ı�����Ԫ�ظ�������ָ��
	DSBPOSITIONNOTIFY * m_pRgDscbpns;
	LPDIRECTSOUNDNOTIFY lpdsn;

	CHLLoopBuff *m_pHLLoopBuff; //���ͻ�����

	WAVEFORMATEX *m_pLesserBufferFormat;//������ʱ�Ĵӻ�������ʽ��������Դ�ĸ�ʽȷ��
	//�������������ĸ�ʽ��Ҫ������ĸ�ʽһ�£�ϵͳȱʡ�ĸ�ʽ�ǣ�����Ƶ��22050Hz��˫������ÿ��������8λ
	WAVEFORMATEX *m_pMainBufferFormat;
	bool m_bLoop; //�Ƿ�ѭ������
	LPDIRECTSOUNDBUFFER lpSoundMainBuff; //��������������ָ��
public: //����
	int GetStatus();
	bool GetSpeakerConfig(DWORD &dwSpeakerConfig);
	virtual void StopReadSoundData();
	bool SetupCaptureEvent(int nEventNum);
	void GetEventList(HANDLE *lpEvents,int &nCount);
	long GetVolume();
	//������д�뻺����
	virtual void WriteSoundData(UINT uSize,DWORD *dwActiveNum) { };
	bool SetLessorBuff(WAVEFORMATEX *pLesserBuff,int iNotify,UINT umillisecond = 2000);
	void SetVolume(long lVolue);
	long GetPan();
	void SetPan(long lPan);
	void SetSpeakerConfig(int nSpeakerConfig);
	virtual void CloseRead() { };
	virtual void Play() ;
	virtual bool BeginWavePlay(char * lpFileName/*,CHLDisplayWaveStatic *pWavStatic=NULL*/) {return false;};
	virtual void ProcessInput( DWORD iEvent ) = 0;
	//�Ƿ���ȫ��������
	//�������������ݶ��뵽lpByte��ָ���ڴ���
	virtual void ReadSoundData(BYTE *lpByte,UINT uNeedCount) { };
	void SetSoundMainBuffer(const WAVEFORMATEX & strWaveFormat);
	virtual inline void SetbLoop(bool bLoop) { m_bLoop = bLoop; }; //����
	inline bool IsLoop() { return m_bLoop; }; ////�����Ƿ���ѭ������
};

//#endif // !defined(AFX_HLVIRSOUNDBUFF_H__975B625E_5C88_471C_8870_2531DDBDD2BA__INCLUDED_)
