// HLFileWavStreamIn.h: interface for the CHLFileWavStreamIn class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_HLFILEWAVSTREAMIN_H__BFAD4AA0_091B_4863_BBBF_CBA2C07AE909__INCLUDED_)
//#define AFX_HLFILEWAVSTREAMIN_H__BFAD4AA0_091B_4863_BBBF_CBA2C07AE909__INCLUDED_

//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
//#include <afxmt.h>
#include "HLVirSoundBuff.h"

#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif

//---------------------------------------------------------------------------------
//             类功能：从WAV文件中读音频数据
//---------------------------------------------------------------------------------
class CHLWavFile;
//class CHLDisplayWaveStatic;
class CLASS_EXPORT CHLFileWavStreamIn : public CHLVirSoundBuff  
{
public:
	enum _WaveFmt
	{
		FMT_WAVFILE = 0, //wav文件
		FMT_DOCWAVFILE ,  //复合文档中的wav文件
		FMT_ENCRYPTWAVEFILE
	};
private:
	CHLWavFile *m_pWaveFile;
	//CCriticalSection m_SectionW;
	CRITICAL_SECTION gSectionW;
	//CString m_strFilePath; //声音文件所在的目录(主要用于复合文档中的声音文件)
	char	m_strFilePath[MAX_PATH];	
	void * m_pFinishPos; // 当不循环播放时，用来确定结束的位置
	bool   m_bPassFileEnd; //已经通过文件的最后位置
	int    m_nTrack;     //声道控制；0：不控制；1：左声道；2：右声道；
private:
	BYTE   *m_pGlobalAllocBuff;
	UINT    m_uGlobalAllocBuff;
public:
	//CHLFileWavStreamIn(HWND hWnd, CString strFilePath="");
	CHLFileWavStreamIn(HWND hWnd, char * lpFileName/* = 0*/);
	virtual ~CHLFileWavStreamIn();
public:
	void ProcessInput( DWORD iEvent );
	void WriteSoundData(UINT uSize,DWORD *dwActiveNum);
	void CloseRead();
    ////double dwPro：声音音量的衰减的百分比(1：原来音量；0.x：为原音量的百分之几)
    bool BeginWavePlay(char * lpFileName,bool bLoop = true, CHLFileWavStreamIn::_WaveFmt eWavFmt = /*FMT_WAVFILE*/FMT_ENCRYPTWAVEFILE, double dwPro = 1, int nTrack = 0/*, CHLDisplayWaveStatic *pWavStatic=NULL*/);
	void ReadSoundData(BYTE *lpByte,UINT uNeedCount);
};

//#endif // !defined(AFX_HLFILEWAVSTREAMIN_H__BFAD4AA0_091B_4863_BBBF_CBA2C07AE909__INCLUDED_)
