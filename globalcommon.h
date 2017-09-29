#ifndef GLOBALCOMMON_H
#define GLOBALCOMMON_H
#include <QString>
#include <QVariant>
#include <QByteArray>
//------------------用户自定义课件结构------------------------
struct userCourseware
{
    QString     m_strCoursewareId;      //课件Id
    QString     m_strCoursewareName;    //课件名
    QString     m_strType;              //课件类型，0为心脏听诊，1为肺部听诊，2为腹部触诊，3为心电图教学
    QString     m_strUrl;               //web网址
};
Q_DECLARE_METATYPE(userCourseware);

//------------------病例结构------------------------
struct stardardCase
{
    QString     m_strCaseId;            //病例id
    QString     m_strName;              //病例名
    QString     m_strType;              //病例类型 0:心音  1:呼吸音  2:肠鸣音
    QString     m_strHuman;             //0:儿童  1:成人  2: 老人
    QByteArray  m_sound_list;           //声音信息
    QString     m_default_sound;        //默认声音
    QString     m_tremble;              //震颤
};
Q_DECLARE_METATYPE(stardardCase);

//------------------鉴别听诊结构------------------------
struct diffSound
{
    QString     m_strType;              //0:心音，1：肺音
    QString     m_strGroupName;         //分类名称
    QString     m_strId;                //鉴别听诊id
    QString     m_strSoundName;         //鉴别听诊名称
    QString     m_strGroupId;           //分类id
};
Q_DECLARE_METATYPE(diffSound);

#endif // GLOBALCOMMON_H
