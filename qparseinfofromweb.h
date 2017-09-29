#ifndef QPARSEINFOFROMWEB_H
#define QPARSEINFOFROMWEB_H
#include "globalcommon.h"
#include <QList>
#include <QObject>
//-----------------解析从web收到的数据------------------------

class QParseInfoFromWeb : public QObject
{
    Q_OBJECT
public:
    QParseInfoFromWeb();
    ~QParseInfoFromWeb();
public:
    //解析自定义课件信息
    void    ParseUsedefineCousewareInfo(const QByteArray& info,QList<userCourseware*>* lstUserCourseware);
    //解析标准病例信息
    void    ParseStardardCaseInfo(const QByteArray& info,QList<stardardCase>* lststardardCase);
    //解析鉴别听诊信息
    void    ParseDiffSoundInfo(const QByteArray& info,QList<diffSound>* lstDiffSound);
};

#endif // QPARSEINFOFROMWEB_H
