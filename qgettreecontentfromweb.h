#ifndef QGETTREECONTENTFROMWEB_H
#define QGETTREECONTENTFROMWEB_H
#include "qparseinfofromweb.h"
#include<QThread>
#include <QObject>


//---------------------获取自定义课件----------------------
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

//--------------------获取标准化病例----------------------------
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


//--------------------获取鉴别听诊--------------------------------
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


//---------------------从web获取自定义课件，标准化病例，鉴别听诊------------------------

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
    //获取自定义课件，标准化病例，鉴别听诊
    void    StartGetContentInfo(QList<userCourseware *>* lstUserCourseware,QList<stardardCase>* lststardardCase,QList<diffSound>* lstDiffSound);
protected:
    QThread             m_workThread;

};

#endif // QGETTREECONTENTFROMWEB_H
