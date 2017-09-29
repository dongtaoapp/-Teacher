#include "qsoundcontrol.h"
#include "qloudauscultategeneralcontrol.h"
#include "qloudauscultatetouchcontrol.h"
#include <QDebug>
//����1:���ھ�� ����2:·�� ����3:����ģ������ ����4:�ķ���������
QSoundControl::QSoundControl(HWND hWnd,QString strAppPath,bool bSimpleAuscultate, bool bSimpleLoud , BOOL bSinglePlayPart)
{
    m_strAppPath      =  strAppPath;
    m_bSinglePlayPart =  bSinglePlayPart;
    m_hWnd     = hWnd;
    if(bSimpleLoud)
    {
        m_pLoudAuscultate = new QLoudAuscultateGeneralControl(m_hWnd,strAppPath);
    }
    else
    {
        m_pLoudAuscultate = new QLoudAuscultateTouchControl(hWnd,strAppPath,bSinglePlayPart);
    }

    m_bSimpleAuscultateMode  = bSimpleAuscultate;
    m_pSoundPlayParts[0] = new QSoundPlayParts(true,strAppPath, bSinglePlayPart ? true : false );
    if( !m_bSinglePlayPart )
    {
        m_pSoundPlayParts[1] = new QSoundPlayParts(false,strAppPath);
    }
    else
    {
        m_pSoundPlayParts[1] = NULL;
    }

    m_bInitial = FALSE;
    m_bEnableSimulateAuscultate = FALSE;

}

QSoundControl::~QSoundControl()
{
    if(m_pLoudAuscultate)
        delete m_pLoudAuscultate;

    for(int n=0; n<2;++n)
    {
        delete m_pSoundPlayParts[n];
    }
    //    qDebug()<<__FUNCTION__;
}

void QSoundControl::SetLoudAuscultateSound(QByteArray strSoundInfo,QString &tremble_position,QString&default_sound)
{
    m_pLoudAuscultate->InitialSoundPart(strSoundInfo,tremble_position,default_sound);
}

void QSoundControl::SetDiffLoudAuscultateSound(QByteArray strInfo1, QByteArray strInfo2)
{
    m_pLoudAuscultate->InitialDiffSoundPart(strInfo1,strInfo2);
}



void QSoundControl::CheckSoundFileDown(QByteArray &array)
{


}

void QSoundControl::LoadSoundConfigue(QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
    m_bInitial = FALSE;

    m_cMutex.lock();

    m_bInitial = TRUE;


    m_pSoundPlayParts[0]->InitialSoundPart(m_hWnd, strSoundInfo,tremble_position,default_sound);
    if( m_pSoundPlayParts[1] )
    {
        m_pSoundPlayParts[1]->InitialSoundPart(m_hWnd, strSoundInfo,tremble_position,default_sound);
    }
    SetLoudAuscultateSound(strSoundInfo,tremble_position,default_sound);
    m_cMutex.unlock();

}

void QSoundControl::LoadDiffSoundConfigue(QByteArray strSoundInfo1, QByteArray strSoundInfo2)
{
    m_bInitial = FALSE;

    m_cMutex.lock();

    m_bInitial = TRUE;

//    SetLoudAuscultateSound(strSoundInfo);
    SetDiffLoudAuscultateSound(strSoundInfo1,strSoundInfo2);

    m_pSoundPlayParts[0]->InitialDiffSoundPart(m_hWnd, strSoundInfo1,strSoundInfo2);
    if( m_pSoundPlayParts[1] )
    {
        m_pSoundPlayParts[1]->InitialDiffSoundPart(m_hWnd, strSoundInfo1,strSoundInfo2);
    }

    m_cMutex.unlock();
}

void QSoundControl::OnAuscultatePosHandle(bool bLeaf, UINT uPos)
{
    if( m_bInitial )
    {
        m_cMutex.lock();
        if( m_bEnableSimulateAuscultate )
        {
            if( bLeaf || m_bSinglePlayPart)
            {
                m_pSoundPlayParts[0]->OnAuscultatePosHandle( uPos );
            }
            else if( m_pSoundPlayParts[1] )
            {
                m_pSoundPlayParts[1]->OnAuscultatePosHandle( uPos );
            }
        }
        else if ( m_pLoudAuscultate->Get_IsLoudAuscultating() )
        {
            m_pLoudAuscultate->OnAuscultatePosHandle(bLeaf, uPos);
        }
        m_cMutex.unlock();
    }
}

void QSoundControl::OnSimulateAuscultateHandle()
{
    if( m_bInitial )
    {
//		停止扩音听诊
        OnStopLoudAuscultate();
        //允许模拟听诊
        m_bEnableSimulateAuscultate = TRUE;
    }
}

void QSoundControl::OnStopSimulateAusculate()
{
    if( m_bInitial )
    {
        //关闭模拟人听�
        m_bEnableSimulateAuscultate = FALSE;
        //停止当前的模拟听�
        m_pSoundPlayParts[0]->StopSimulateAuscultate();
        if( m_pSoundPlayParts[1] )
        {
            m_pSoundPlayParts[1]->StopSimulateAuscultate();
        }
    }
}

void QSoundControl::OnLoudAuscultateHandle()
{
    if( m_bInitial && m_pLoudAuscultate->Get_IsEnableLoudAuscultate() )
    {
        //停止模拟听诊
        OnStopSimulateAusculate();
        //m_pLoudAuscultate->SetPan(-10000);
        //播放扩音听诊
        m_pLoudAuscultate->StartLoudAuscultateHandle();
    }
}

void QSoundControl::OnStopLoudAuscultate()
{
    m_pLoudAuscultate->StopLoudAuscultate();
}

bool QSoundControl::IsCanSimulateAuscultate()
{
    return m_bInitial;
}

BOOL QSoundControl::IsCanLoudAuscultate()
{
    if( m_bInitial && m_pLoudAuscultate->Get_IsEnableLoudAuscultate() )
    {
        return TRUE;
    }
    return FALSE;
}

bool QSoundControl::GetHeartVibrPosValue(BYTE *pbytePos)
{
    if( !m_bInitial )
    {
        return FALSE;
    }
    QSoundPlayParts *pSoundParts = NULL;
    if( m_pSoundPlayParts[0] != NULL )
    {
        pSoundParts = m_pSoundPlayParts[0];
    }
    else if( m_pSoundPlayParts[1] != NULL )
    {
        pSoundParts = m_pSoundPlayParts[1];
    }
    if( pSoundParts == NULL )
    {
        return FALSE;
    }
    //查找震颤位置列表
    return pSoundParts->GetHeartVibrPos( /*out*/pbytePos );
}

QString QSoundControl::GetPosString(BOOL bHeartSound)
{
    if( m_pSoundPlayParts[0] != NULL )
        return m_pSoundPlayParts[0]->GetPosString(bHeartSound);
    return "-1";
}
