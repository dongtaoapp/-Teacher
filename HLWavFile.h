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
	bool        m_bReadOver; //�������е�����
public:
	//���ֵ�ǰ��û���������Ĵ�С���ں���WaveStartDataRead�б���ʼ����
	MMCKINFO m_CkCurrInfo;
	bool m_bLoop; //�Ƿ�ѭ��
	//WaveFormatEx structure with all info about the file
	WAVEFORMATEX *m_pWaveFormatEx;
public:
	//�����Ƿ��������ݶ�����

	inline bool IsReadWaveDataOver() { return m_bReadOver;};

	virtual int WaveReadData(BYTE *pDest,UINT nCount, int nTrack = 0);
	virtual int WaveStartDataRead();
	virtual void WaveCloseReadFile();
	virtual int WaveOpenFile(char *pszFileName);
protected: //��������
	void WavSoundTrackControl(BYTE *lptrData, UINT uLength, int nTrack);
};

