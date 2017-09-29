#pragma once
#include "HLWavFile.h"

class /*CLASS_EXPORT*/ CHLEncryptWaveFile :
	public CHLWavFile
{
public:
	CHLEncryptWaveFile(void);
	~CHLEncryptWaveFile(void);
	
public:
	int WaveReadData(BYTE *pDest,UINT nCount,int nTrack = 0);
	int Test();
};