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
//   类的功能：音频输入源的基类；是纯虚类。音频输入源可由WAV文件和网络传入两方面得到。
//             类中有逻辑上是环形的内存缓冲区，作为向CHLWavStreamOut的声音源.
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
	HWND            m_hWnd; //窗口句柄
public:
	CHLVirSoundBuff(HWND hWnd);
	virtual ~CHLVirSoundBuff();
public:
	//CCriticalSection m_Section2;
	CRITICAL_SECTION gSection;
	HANDLE           m_hThreadOutEvent;   //线程退出事件
protected:
	HANDLE   m_hEventFinish; //控制线程的结束
protected:
	bool Initialize(WAVEFORMATEX *pLesserFormat,UINT umillisecond = 4000);

	LPDIRECTSOUND m_pDirectSound; //DirectSound对象

	UINT m_nNotifyNum; //DSBPOSITIONNOTIFY结构数组中元素的个数
	//DSBPOSITIONNOTIFY结构数组，每一个与捕获缓冲区相联系的事件都需要一个该
	//数组的变量。元素个数有外指定
	DSBPOSITIONNOTIFY * m_pRgDscbpns;
	LPDIRECTSOUNDNOTIFY lpdsn;

	CHLLoopBuff *m_pHLLoopBuff; //环型缓冲区

	WAVEFORMATEX *m_pLesserBufferFormat;//放声音时的从缓冲区格式，由输入源的格式确定
	//声卡主缓冲区的格式，要与采样的格式一致，系统缺省的格式是：采样频率22050Hz，双声道，每个采样点8位
	WAVEFORMATEX *m_pMainBufferFormat;
	bool m_bLoop; //是否循环声音
	LPDIRECTSOUNDBUFFER lpSoundMainBuff; //声卡的主缓冲区指针
public: //函数
	int GetStatus();
	bool GetSpeakerConfig(DWORD &dwSpeakerConfig);
	virtual void StopReadSoundData();
	bool SetupCaptureEvent(int nEventNum);
	void GetEventList(HANDLE *lpEvents,int &nCount);
	long GetVolume();
	//将内容写入缓冲区
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
	//是否已全部都放完
	//将缓冲区的数据读入到lpByte所指的内存中
	virtual void ReadSoundData(BYTE *lpByte,UINT uNeedCount) { };
	void SetSoundMainBuffer(const WAVEFORMATEX & strWaveFormat);
	virtual inline void SetbLoop(bool bLoop) { m_bLoop = bLoop; }; //设置
	inline bool IsLoop() { return m_bLoop; }; ////返回是否是循环播放
};

//#endif // !defined(AFX_HLVIRSOUNDBUFF_H__975B625E_5C88_471C_8870_2531DDBDD2BA__INCLUDED_)
