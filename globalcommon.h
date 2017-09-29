#ifndef GLOBALCOMMON_H
#define GLOBALCOMMON_H
#include <QString>
#include <QVariant>
#include <QByteArray>
//------------------�û��Զ���μ��ṹ------------------------
struct userCourseware
{
    QString     m_strCoursewareId;      //�μ�Id
    QString     m_strCoursewareName;    //�μ���
    QString     m_strType;              //�μ����ͣ�0Ϊ�������1Ϊ�β����2Ϊ�������3Ϊ�ĵ�ͼ��ѧ
    QString     m_strUrl;               //web��ַ
};
Q_DECLARE_METATYPE(userCourseware);

//------------------�����ṹ------------------------
struct stardardCase
{
    QString     m_strCaseId;            //����id
    QString     m_strName;              //������
    QString     m_strType;              //�������� 0:����  1:������  2:������
    QString     m_strHuman;             //0:��ͯ  1:����  2: ����
    QByteArray  m_sound_list;           //������Ϣ
    QString     m_default_sound;        //Ĭ������
    QString     m_tremble;              //���
};
Q_DECLARE_METATYPE(stardardCase);

//------------------��������ṹ------------------------
struct diffSound
{
    QString     m_strType;              //0:������1������
    QString     m_strGroupName;         //��������
    QString     m_strId;                //��������id
    QString     m_strSoundName;         //������������
    QString     m_strGroupId;           //����id
};
Q_DECLARE_METATYPE(diffSound);

#endif // GLOBALCOMMON_H
