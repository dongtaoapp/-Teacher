#ifndef QCOURSEWAREINFO_H
#define QCOURSEWAREINFO_H

#include <QObject>
#include <QJsonArray>
#include <QVariant>
#include <QMetaType>
//Q_DECLARE_METATYPE(QMap<QString,QCoursewareInfo*>)




//--------------------璇句欢淇℃伅绫-------------------------------

#if 0
class QCoursewareInfo : public QObject
{
    Q_OBJECT
public:
    explicit QCoursewareInfo(QObject *parent = 0);
    ~QCoursewareInfo();
public:
    QString      m_strCoursewareName; //璇句欢鍚
    QString      m_strTreeDir;    //鏍戝舰缁撴瀯
    QString      m_strFlash;      //flash鏂囦欢鍚
    QString      m_strNetId;      //web瀵瑰簲鐨刬d
    int          sonClsaa;
public:
    QString     GetCoursewareName() { return m_strCoursewareName; }
    void        SetCoursewareName(QString strCoursewareName) { m_strCoursewareName = strCoursewareName;}
    QString     GetTreeDir() { return m_strTreeDir; }
    void        SetTreeDir(QString strTreeDir) { m_strTreeDir = strTreeDir;}
    QString     GetFlash() { return m_strFlash; }
    void        SetFlash(QString strFlash) { m_strFlash = strFlash;}
    QString     GetNetId() { return m_strNetId; }
    void        SetNetId(QString strNetId) { m_strNetId = strNetId;}
signals:

public slots:
};
#endif
typedef struct QCoursewareInfo
{
    QString      m_strCoursewareName; //璇句欢鍚
    QString      m_strTreeDir;    //鏍戝舰缁撴瀯
    QString      m_strFlash;      //flash鏂囦欢鍚
    QString      m_strNetId;      //web瀵瑰簲鐨刬d
    QString      m_CaseID;       //CaseID
    int          sonClsaa;
    QString      m_defalut_sound;
    QString      m_tremble_position;
    QByteArray   m_sound_list;

}QCoursewareInfo;

Q_DECLARE_METATYPE(QCoursewareInfo)

QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< QMap<QString,QCoursewareInfo*> >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
    {
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
        if (!metatype_id)
            metatype_id = qRegisterMetaType< QMap<QString,QCoursewareInfo*> >("QMap<QString,QCoursewareInfo*>",
                reinterpret_cast< QMap<QString,QCoursewareInfo*> *>(quintptr(-1)));
        return metatype_id;
    }
};
QT_END_NAMESPACE

#endif // QCOURSEWAREINFO_H
