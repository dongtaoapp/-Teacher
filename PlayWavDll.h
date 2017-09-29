#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <dsound.h>

//#include "HLWavFile.h"
//#include "HLDocWavFile.h"
//#include "HLEncryptWaveFile.h"
//#include "HLLoopBuff.h"
//#include "HLVirSoundBuff.h"
//#include "HLWavStreamOut.h"
#include "HLFileWavStreamIn.h"


#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif









//-----------------------------------------------------------------------------------





////class PlayWavDll_1;
//class  PlayWavDll
//{
//	//friend PlayWavDll_1;
//public:
//	PlayWavDll(void);
//	~PlayWavDll(void);
//
//	//PlayWavDll_1 *p;
//};

class CLASS_EXPORT PlayWavDll_1 /*: PlayWavDll*/
{
public:
	PlayWavDll_1(void);
	~PlayWavDll_1(void);
	//PlayWavDll *p;


};