#ifndef QCOMORDER_H
#define QCOMORDER_H
#include<QByteArray>
#include<Windows.h>
#include <QVariant>


struct comDataStruct
{
public:
    QByteArray m_data;
    BYTE   m_byMainAddress;     //����ַ
    BYTE   m_byMinorAddress;    //�ӵ�ַ
    int     m_nCmdType;         //-1�������ͣ�0��ģ����Ͳλ�ã�1������λ�ã�2�����Ͳ�ѯλ��
    BOOL   m_bAuscultate;       //�Ƿ���������
public:
    comDataStruct()
    {
        m_nCmdType = -1;
    }
};


Q_DECLARE_METATYPE(comDataStruct);

//--------------comָ����----------------------------------

class QComOrder
{
public:
    QComOrder();
public:
    //���ؽ�ѧģʽ��Ӧ���·�ָ��
    void    GetTeachModeOrder(int nMode,QByteArray& data);  //0Ϊ��ѧ���⣬1Ϊģ�����2Ϊ��������
    //�������λ��ָ��
    void    GetVidrPosOrder(BYTE pos, QByteArray& data);
    //����ֹͣ���ָ��
    void    GetStopVidrOrder(QByteArray& data);
    //����com�յ�����
    void    ParseComReadData(QByteArray& data,QList<comDataStruct*>& lstdata);
    //��ȡ��������
    void    GetPalpateOrder(QByteArray& data,int nOrderNo);
    //��ȡ����������ָ��
    void    GetAuscultateLinkOrder(QByteArray& data);
    //����ģ�����ϴ�������ָ��
    int    ParseLinkOrder(const QByteArray& data); //����-1����Чָ�0����ʦ�����ƺУ�1��ѧ�������ƺ�
    //��ȡ����������ָ��
    void    GetPalpateLinkOrder(QByteArray& data);
protected:
    comDataStruct* GetDataSturctFromData(QByteArray& data);
    //������ʼ��־
    bool SearchBeginFlag(QByteArray& data);
    //����β��־�����������
    int  SearchEndFlag(const QByteArray& data);
    void JugdeDataType(comDataStruct* pData);
};



#endif // QCOMORDER_H
