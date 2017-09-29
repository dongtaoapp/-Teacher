#ifndef QCOMORDER_H
#define QCOMORDER_H
#include<QByteArray>
#include<Windows.h>
#include <QVariant>


struct comDataStruct
{
public:
    QByteArray m_data;
    BYTE   m_byMainAddress;     //主地址
    BYTE   m_byMinorAddress;    //从地址
    int     m_nCmdType;         //-1：无类型，0：模拟听筒位置，1：触诊位置，2：回送查询位置
    BOOL   m_bAuscultate;       //是否听诊命令
public:
    comDataStruct()
    {
        m_nCmdType = -1;
    }
};


Q_DECLARE_METATYPE(comDataStruct);

//--------------com指令类----------------------------------

class QComOrder
{
public:
    QComOrder();
public:
    //返回教学模式对应的下发指令
    void    GetTeachModeOrder(int nMode,QByteArray& data);  //0为教学讲解，1为模拟听诊，2为扩音听诊
    //返回震颤位置指令
    void    GetVidrPosOrder(BYTE pos, QByteArray& data);
    //返回停止震颤指令
    void    GetStopVidrOrder(QByteArray& data);
    //解析com收到数据
    void    ParseComReadData(QByteArray& data,QList<comDataStruct*>& lstdata);
    //获取触诊命令
    void    GetPalpateOrder(QByteArray& data,int nOrderNo);
    //获取听诊人联机指令
    void    GetAuscultateLinkOrder(QByteArray& data);
    //解析模拟人上传的联机指令
    int    ParseLinkOrder(const QByteArray& data); //返回-1：无效指令，0：教师机控制盒，1：学生机控制盒
    //获取触诊人联机指令
    void    GetPalpateLinkOrder(QByteArray& data);
protected:
    comDataStruct* GetDataSturctFromData(QByteArray& data);
    //查找起始标志
    bool SearchBeginFlag(QByteArray& data);
    //查找尾标志，返回命令长度
    int  SearchEndFlag(const QByteArray& data);
    void JugdeDataType(comDataStruct* pData);
};



#endif // QCOMORDER_H
