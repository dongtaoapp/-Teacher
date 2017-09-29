// HLWavStreamOut.h: interface for the CHLWavStreamOut class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_HLWAVSTREAMOUT_H__B31A4B78_0327_48F2_A428_578DD8D23375__INCLUDED_)
//#define AFX_HLWAVSTREAMOUT_H__B31A4B78_0327_48F2_A428_578DD8D23375__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif


//----------------------------------------------------------------------------------
//               �๦�ܣ����ƴӻ��������������ˡ�
//----------------------------------------------------------------------------------
class CHLVirSoundBuff;
//class CHLDisplayWaveStatic;
class CLASS_EXPORT CHLWavStreamOut  
{
public:
	bool Initialize(CHLVirSoundBuff *pHLSoundBuff, LPDIRECTSOUND lpDirectSound,LPWAVEFORMATEX lpFormat,UINT uMillisecond,int iNotify);
	void SetLesserFormat(WAVEFORMATEX *pWaveFormat);
	CHLWavStreamOut();
	virtual ~CHLWavStreamOut();

public:
	//���ܣ�����״̬ //����ֵ��  -1�����ڹر�״̬;0��������ͣ״̬;1�����ڲ���״̬
	inline int GetStatus() { return m_nStatus; };
	inline void SetStatus(int nStatus) {m_nStatus = nStatus;};
	void StopWaveStream();
	void Play();
	void CloseWavStreamOut();
	void ProcessInput(DWORD dEvent);
	void GetEventList(HANDLE *lpEvents, int &nCount);
	bool SetupCaptureEvent(/*CHLDisplayWaveStatic *pWaveStc,*/int nEventNum);
	LPDIRECTSOUNDBUFFER lpSoundLesserBuff;
	DWORD dBufferSize;
	WAVEFORMATEX * m_pLesserBufferFormat;
private:
	CHLVirSoundBuff     *m_pHLVirSoundBuff;
	DSBPOSITIONNOTIFY * m_pRgDscbpns; //����������ǰ���ŵ�λ��
	UINT                m_nNotifyNum;
	LPDIRECTSOUNDNOTIFY lpdsn;//��������ʱ�����Ĵӻ�����ָ��
	HANDLE              m_hFinishEvent; //���ƽ����̵߳��¼�
	HANDLE              m_hReadFnsEvt; //��λ�ý���ʱ���¼�
	int                 m_nBlockAlign;
	//CHLDisplayWaveStatic *m_pDisplayWaveStc;
	int                 m_nStatus; //״̬
public:
	HANDLE              m_hThreadFinishEvent;//�߳̽������¼�
};

//#endif // !defined(AFX_HLWAVSTREAMOUT_H__B31A4B78_0327_48F2_A428_578DD8D23375__INCLUDED_)
