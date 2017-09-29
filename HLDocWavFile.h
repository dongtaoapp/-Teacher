#pragma once
#include "HLWavFile.h"
//#define DLLTEST_EXPORTS
//#ifdef DLLTEST_EXPORTS
//	#define CLASS_EXPORT __declspec(dllexport)
//#else
//	#define CLASS_EXPORT __declspec(dllimport)
//#endif


////class PlayWavDll_1;
//class CLASS_EXPORT PlayWavDll
//{
//	//friend PlayWavDll_1;
//public:
//	PlayWavDll(void);
//	~PlayWavDll(void);
//public:
//	virtual void Test();
//	//PlayWavDll_1 *p;
//	
//};

class CHLDocWavFile : public CHLWavFile
{
private:
	LPSTREAM m_lpStream;
	LPSTORAGE m_lpStorage;
	LPSTORAGE m_lpChildStorage;
	CString m_strFilePath; //声音文件所在的目录
public:
	CHLDocWavFile(CString strFilePath);
	//CHLDocWavFile(char* pFilePath);
	CHLDocWavFile();
	virtual ~CHLDocWavFile();
public:
	int WaveReadData(BYTE *pDest,UINT nCount, int nTrack = 0);
	void WaveCloseReadFile();
	int WaveStartDataRead();
	int WaveOpenFile(char *pszFileName);
};



