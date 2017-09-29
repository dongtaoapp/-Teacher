#ifndef QPARSEINFOFROMWEB_H
#define QPARSEINFOFROMWEB_H
#include "globalcommon.h"
#include <QList>
#include <QObject>
//-----------------������web�յ�������------------------------

class QParseInfoFromWeb : public QObject
{
    Q_OBJECT
public:
    QParseInfoFromWeb();
    ~QParseInfoFromWeb();
public:
    //�����Զ���μ���Ϣ
    void    ParseUsedefineCousewareInfo(const QByteArray& info,QList<userCourseware*>* lstUserCourseware);
    //������׼������Ϣ
    void    ParseStardardCaseInfo(const QByteArray& info,QList<stardardCase>* lststardardCase);
    //��������������Ϣ
    void    ParseDiffSoundInfo(const QByteArray& info,QList<diffSound>* lstDiffSound);
};

#endif // QPARSEINFOFROMWEB_H
