#ifndef QGETTREECONTENTFROMWEB_H
#define QGETTREECONTENTFROMWEB_H
#include "qparseinfofromweb.h"
#include<QThread>
#include <QObject>


//---------------------��ȡ�Զ���μ�----------------------
class QGetContentWork : public QObject
{
    Q_OBJECT
public:
    explicit QGetContentWork(QObject *parent = 0);

signals:
    void    Finish();
public slots:
    void DoParseUserCourseware(const QByteArray& byte);
    void DoParseStandardCase(const QByteArray& byte);
    void DoParseDifferAuscult(const QByteArray& byte);
public:
    void StartGet(QList<userCourseware *>* lstUserCourseware,QList<stardardCase>* lststardardCase,QList<diffSound>* lstDiffSound);
protected:
    QList<userCourseware *>*    m_ptrLstUserCourseware;
    QList<stardardCase >*      m_ptrLststardardCase;
    QList<diffSound >*         m_ptrLstDiffSound;
    QParseInfoFromWeb           m_parseInfoFromWeb;
};

//--------------------��ȡ��׼������----------------------------
class QGetStandardCase : public QObject
{
    Q_OBJECT
public:
    explicit QGetStandardCase(QObject *parent = 0);

signals:
    void    Finish();
public slots:

public:
    void ParseStandardCase(QList<stardardCase >* lststardardCase);
    void DoParseFromWeb(const QByteArray& byte);
protected:
    QList<stardardCase >* m_ptrLststardardCase;
};


//--------------------��ȡ��������--------------------------------
class QGetDifferAuscult : public QObject
{
    Q_OBJECT
public:
    explicit QGetDifferAuscult(QObject *parent = 0);

signals:
    void    Finish();
public slots:

public:
    void ParseDifferAuscult(QList<diffSound *>* lstDiffSound);
    void DoParseFromWeb(const QByteArray& byte);
protected:
    QList<diffSound *>* m_ptrLstDiffSound;
};


//---------------------��web��ȡ�Զ���μ�����׼����������������------------------------

class QGetTreeContentFromWeb : public QObject
{
    Q_OBJECT
public:
    explicit QGetTreeContentFromWeb(QObject *parent = 0);
    ~QGetTreeContentFromWeb();

signals:
    void FinishGet();
public slots:
    void Finish();

public:
    //��ȡ�Զ���μ�����׼����������������
    void    StartGetContentInfo(QList<userCourseware *>* lstUserCourseware,QList<stardardCase>* lststardardCase,QList<diffSound>* lstDiffSound);
protected:
    QThread             m_workThread;

};

#endif // QGETTREECONTENTFROMWEB_H
