#include "qloudauscultatetouchcontrol.h"
#include <qDebug>
QLoudAuscultateTouchControl::QLoudAuscultateTouchControl(HWND hWnd, QString strAppPath, bool bSinglePlayPart):QLoudAuscultateControlVir(hWnd,strAppPath)
{
    m_hWnd = hWnd;
    m_bSinglePlayPart = bSinglePlayPart;
    m_pSoundPlayParts[0] = new QLoudAuscultateTouchPlayParts(true,strAppPath,bSinglePlayPart?true:false);
    if(!bSinglePlayPart)
    {
        m_pSoundPlayParts[1] = new QLoudAuscultateTouchPlayParts(false,strAppPath);
    }
    else
        m_pSoundPlayParts[1] = NULL;
}

QLoudAuscultateTouchControl::~QLoudAuscultateTouchControl()
{
    for(int n =0 ; n < 2; n++)
    {
        delete m_pSoundPlayParts[n];
    }
}
//----------------------Ó²¼þÍ¨ÐÅÀ©ÒôÌýÕï
void QLoudAuscultateTouchControl::InitialSoundPart(QByteArray strSoundInfo,QString &tremble_position,QString &default_sound)
{
    qDebug()<<__FUNCTION__<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    m_bEnableLoudAuscultate = m_pSoundPlayParts[0]->InitialLoadLoudSound(m_hWnd,strSoundInfo,tremble_position,default_sound);

    if(m_bEnableLoudAuscultate && m_pSoundPlayParts[1])
    {
        m_pSoundPlayParts[1]->InitialLoadLoudSound(m_hWnd,strSoundInfo,tremble_position,default_sound);
    }
}

void QLoudAuscultateTouchControl::InitialDiffSoundPart(QByteArray strSoundInfo1, QByteArray strSoundInfo2)
{

}

void QLoudAuscultateTouchControl::OnAuscultatePosHandle(bool bLeaf, UINT uPos)
{
    if( m_bEnableLoudAuscultate )
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
}



//if(m_bEnableLoudAuscultate /*&& m_pLoudAuscultate->GetStatus() != 1*/)
//{
//    if(m_bDefaultNow)
//    {
//        if(m_pLoudAuscultate->GetStatus() != 1)
//        {
//            qDebug()<<"+++++++++++++++++++++++++++++++++++++";
//            m_pLoudAuscultate->Play();
//            m_bLoudAuscultating = TRUE;
//        }
//    }
//    else
//    {
//        if(m_pUserDefineLoudAuscultate->GetStatus() != 1)
//        {
//            qDebug()<<"=======================================";
//            m_pUserDefineLoudAuscultate->Play();
//            m_bLoudAuscultating = TRUE;
//        }
//    }

//}

void QLoudAuscultateTouchControl::StartLoudAuscultateHandle()
{
    if(m_bEnableLoudAuscultate)
        m_bLoudAuscultating = TRUE;
}

void QLoudAuscultateTouchControl::StopLoudAuscultate()
{
    m_bLoudAuscultating = FALSE;
}
