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
//             �๦�ܣ���WAV�ļ��ж���Ƶ����
//---------------------------------------------------------------------------------
class CHLWavFile;
//class CHLDisplayWaveStatic;
class CLASS_EXPORT CHLFileWavStreamIn : public CHLVirSoundBuff  
{
public:
	enum _WaveFmt
	{
		FMT_WAVFILE = 0, //wav�ļ�
		FMT_DOCWAVFILE ,  //�����ĵ��е�wav�ļ�
		FMT_ENCRYPTWAVEFILE
	};
private:
	CHLWavFile *m_pWaveFile;
	//CCriticalSection m_SectionW;
	CRITICAL_SECTION gSectionW;
	//CString m_strFilePath; //�����ļ����ڵ�Ŀ¼(��Ҫ���ڸ����ĵ��е������ļ�)
	char	m_strFilePath[MAX_PATH];	
	void * m_pFinishPos; // ����ѭ������ʱ������ȷ��������λ��
	bool   m_bPassFileEnd; //�Ѿ�ͨ���ļ������λ��
	int    m_nTrack;     //�������ƣ�0�������ƣ�1����������2����������
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
    ////double dwPro������������˥���İٷֱ�(1��ԭ��������0.x��Ϊԭ�����İٷ�֮��)
    bool BeginWavePlay(char * lpFileName,bool bLoop = true, CHLFileWavStreamIn::_WaveFmt eWavFmt = /*FMT_WAVFILE*/FMT_ENCRYPTWAVEFILE, double dwPro = 1, int nTrack = 0/*, CHLDisplayWaveStatic *pWavStatic=NULL*/);
	void ReadSoundData(BYTE *lpByte,UINT uNeedCount);
};

//#endif // !defined(AFX_HLFILEWAVSTREAMIN_H__BFAD4AA0_091B_4863_BBBF_CBA2C07AE909__INCLUDED_)
