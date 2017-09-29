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
//               类功能：控制从缓冲区的数据流人。
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
	//功能：返回状态 //返回值：  -1：处于关闭状态;0：处于暂停状态;1：处于播放状态
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
	DSBPOSITIONNOTIFY * m_pRgDscbpns; //用于描述当前播放的位置
	UINT                m_nNotifyNum;
	LPDIRECTSOUNDNOTIFY lpdsn;//播放声音时声卡的从缓冲区指针
	HANDLE              m_hFinishEvent; //控制结束线程的事件
	HANDLE              m_hReadFnsEvt; //读位置结束时的事件
	int                 m_nBlockAlign;
	//CHLDisplayWaveStatic *m_pDisplayWaveStc;
	int                 m_nStatus; //状态
public:
	HANDLE              m_hThreadFinishEvent;//线程结束的事件
};

//#endif // !defined(AFX_HLWAVSTREAMOUT_H__B31A4B78_0327_48F2_A428_578DD8D23375__INCLUDED_)
