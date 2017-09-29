// HLLoopBuff.h: interface for the CHLLoopBuff class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_HLLOOPBUFF_H__99F89DAE_80DA_41FA_9D01_229BA9BAD7D2__INCLUDED_)
//#define AFX_HLLOOPBUFF_H__99F89DAE_80DA_41FA_9D01_229BA9BAD7D2__INCLUDED_
//
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
//#include <afxmt.h>

#define DLLTEST_EXPORTS
#ifdef DLLTEST_EXPORTS
	#define CLASS_EXPORT __declspec(dllexport)
#else
	#define CLASS_EXPORT __declspec(dllimport)
#endif


//-----------------------环行缓冲类---------------------------------------
class CLASS_EXPORT CHLLoopBuff  
{
public:
	inline BYTE * GetEndPtr() {return m_pEndPos; };
	inline BYTE * GetBeginPtr() {return m_pBeginPos; };
	inline DWORD GetBufferSize() {return m_dLoopBuffNum - 1; };

	void ReadData(BYTE *lpByte,DWORD dNeedCount,DWORD *dActiveSize = NULL);
	void WriteData(BYTE *pInData,DWORD dSize,DWORD *dwActiveNum = NULL);
	DWORD GetCurrBufferNum();
	void Empty();
	bool InitializeBuff(DWORD dSize);
	CHLLoopBuff();
	virtual ~CHLLoopBuff();
protected:
	BYTE * m_pLoopByteBuff; //缓冲区
	DWORD  m_dLoopBuffNum; //内存缓冲区的大小
	BYTE * m_pEndPos;   //在逻辑环形缓冲区中的有效声音结束位置
	BYTE * m_pBeginPos; //在逻辑环形缓冲区中的有效声音开始位
	//CCriticalSection m_Section[3];
	CRITICAL_SECTION gSection[3];
};

//#endif // !defined(AFX_HLLOOPBUFF_H__99F89DAE_80DA_41FA_9D01_229BA9BAD7D2__INCLUDED_)
