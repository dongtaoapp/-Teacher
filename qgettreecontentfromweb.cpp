#include "qgettreecontentfromweb.h"
#include<QDebug>


QGetContentWork::QGetContentWork(QObject *parent) : QObject(parent)
{
    m_ptrLstUserCourseware = NULL;
    m_ptrLststardardCase = NULL;
    m_ptrLstDiffSound = NULL;
}

void QGetContentWork::StartGet(QList<userCourseware *>* lstUserCourseware,QList<stardardCase>* lststardardCase,QList<diffSound>* lstDiffSound)
{
    m_ptrLstUserCourseware = lstUserCourseware;
    m_ptrLststardardCase = lststardardCase;
    m_ptrLstDiffSound = lstDiffSound;
    //向web请求信息


//    //test
//    QByteArray byte;
    //m_parseInfoFromWeb.ParseUsedefineCousewareInfo(byte,m_ptrLstUserCourseware);
//    emit Finish();
}

void QGetContentWork::DoParseUserCourseware(const QByteArray &byte)
{

    m_parseInfoFromWeb.ParseUsedefineCousewareInfo(byte,m_ptrLstUserCourseware);
     //向web请求信息
}

void QGetContentWork::DoParseStandardCase(const QByteArray &byte)
{
    m_parseInfoFromWeb.ParseStardardCaseInfo(byte,m_ptrLststardardCase);
    //向web请求信息
}


void QGetContentWork::DoParseDifferAuscult(const QByteArray &byte)
{
    m_parseInfoFromWeb.ParseDiffSoundInfo(byte,m_ptrLstDiffSound);
    emit Finish();
}


//--------------------------------------------------------------------------------
QGetStandardCase::QGetStandardCase(QObject *parent) : QObject(parent)
{
    m_ptrLststardardCase = NULL;
}

void QGetStandardCase::ParseStandardCase(QList<stardardCase > *lststardardCase)
{
     m_ptrLststardardCase = lststardardCase;
}

void QGetStandardCase::DoParseFromWeb(const QByteArray &byte)
{
    QParseInfoFromWeb parseInfoFromWeb;
    parseInfoFromWeb.ParseStardardCaseInfo(byte,m_ptrLststardardCase);
    emit Finish();
}


//---------------------------------------------------------------------------------
QGetDifferAuscult::QGetDifferAuscult(QObject *parent) : QObject(parent)
{

}

void QGetDifferAuscult::ParseDifferAuscult(QList<diffSound *> *lstDiffSound)
{

}

void QGetDifferAuscult::DoParseFromWeb(const QByteArray &byte)
{

}



//---------------------------------------------------------------------------------
QGetTreeContentFromWeb::QGetTreeContentFromWeb(QObject *parent) : QObject(parent)
{
//    QList<userCourseware *> lstUserCourseware;
//    QParseInfoFromWeb parseInfoFromWeb;
//    QByteArray byte;
//    parseInfoFromWeb.ParseUsedefineCousewareInfo(byte,&lstUserCourseware);
//    for(int i = 0; i < lstUserCourseware.size();i++)
//    {
//        userCourseware *p = lstUserCourseware.at(i);
//        qDebug()<<p->m_strCoursewareId<<p->m_strCoursewareName<<p->m_strType<<p->m_strUrl;
//        }

    m_workThread.start();
}

QGetTreeContentFromWeb::~QGetTreeContentFromWeb()
{
    m_workThread.requestInterruption();
    m_workThread.quit();
    m_workThread.wait();
}

void QGetTreeContentFromWeb::Finish()
{
    emit FinishGet();

}

void QGetTreeContentFromWeb::StartGetContentInfo(QList<userCourseware *> *lstUserCourseware, QList<stardardCase > *lststardardCase, QList<diffSound > *lstDiffSound)
{
    QGetContentWork* pGetContentWork = new QGetContentWork;
    pGetContentWork->moveToThread(&m_workThread);

    connect(&m_workThread,&QThread::finished,pGetContentWork,&QObject::deleteLater);
    connect(pGetContentWork,&QGetContentWork::Finish,this,&QGetTreeContentFromWeb::Finish);

    pGetContentWork->StartGet(lstUserCourseware,lststardardCase,lstDiffSound);

}
