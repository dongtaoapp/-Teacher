#pragma once
#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif

class CLASS_EXPORT CHLWavFile  
{
public:
	CHLWavFile(void);
	virtual ~CHLWavFile(void);
protected:
	MMIOINFO    mmioinfoIn;         // current status of <hmmioIn>
	//main chuck
	MMCKINFO m_CkRiffInfo;
	HMMIO m_hMmio;  //Handle to mmio
protected:
	bool        m_bReadOver; //读完所有的数据
public:
	//保持当前还没读的声音的大小，在函数WaveStartDataRead中被初始化。
	MMCKINFO m_CkCurrInfo;
	bool m_bLoop; //是否循环
	//WaveFormatEx structure with all info about the file
	WAVEFORMATEX *m_pWaveFormatEx;
public:
	//返回是否声音数据都读完

	inline bool IsReadWaveDataOver() { return m_bReadOver;};

	virtual int WaveReadData(BYTE *pDest,UINT nCount, int nTrack = 0);
	virtual int WaveStartDataRead();
	virtual void WaveCloseReadFile();
	virtual int WaveOpenFile(char *pszFileName);
protected: //声道控制
	void WavSoundTrackControl(BYTE *lptrData, UINT uLength, int nTrack);
};

