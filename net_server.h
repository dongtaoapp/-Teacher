#ifndef NET_SERVER_H
#define NET_SERVER_H
#include "define.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QStringList>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMutex>

#include <QUdpSocket>



class net_server_socket:public QTcpSocket
{
  Q_OBJECT
public:
    net_server_socket();
    ~net_server_socket();

    qintptr returnDescriptor();

public slots:

    void onreadyRead();

    void ondisconnected();

signals:

    void signal_recv(QByteArray &recvMsg);

    void signal_descriptor(qintptr descriptor);
};


class net_server : public QTcpServer
{
    Q_OBJECT
public:
    net_server(QObject *parent=Q_NULLPTR);
    ~net_server();
    void sendString(QString &str);//�����ַ���
    QByteArray TellClientConnectedSuucess(QString &str);//����ѧ�����Ѿ����ӳɹ�
    bool setserverlisten(quint16 port);//���÷���˼����Ķ˿�

    void sendMsgtoClient(QByteArray &msg);


    QList<ClientIdIp> clientinfoList(){return clientIdIp_List;}

public:
//    void control_talk_authority(QString &ip,QString &ipList,bool talk);//�Խ�


    void ControlTalk(QString ip,bool order);

    void allTeach_auscultar(bool cmd);//������ƽӿ� true �ǽ�������

    void allTeach_contralplayflash();//�����Ƿ񲥷�flash

//    void allTeach_courseware(QString &flashpath);//flash �л� flashpath��flash·��

    void allTeach_exam(bool cmd,int exam_id=-1);//�Ƿ���п���

    void allTeach_train(bool cmd,int train_id=-1);//����ѵ��

    void allTeach_closeall();//ȫ��ػ�


public slots:
    //----------------ͬ����ѧ�����ӿ�
    void startAllTeach(bool cmd);//��ʼ����ͬ����ѧ
    void ALLTeachActionTab(int tab);
    void ALLTeachActionBtn(QString &action);//����ͼ����
    void ALLTeachActionDiffItem(QString &ID);//������������ͼ����
    void ALLTeachActionDiffItemDelete(QString index);//ɾ��������������
    void ALLTeachActionDiffItemLoad();//LOAD����
    void ALLTrachLocalFlash(QString &flashName);//���ر���flash
    void ALLTeachLocalCase(QString &ID);
    void ALLTeachWork(QString &work);//�����Ƿ񲥷�flash
    void ALLTeacherPatter(QString patter);
    void ondisconnected(qintptr descriptor);

    void onRecvmsg(QByteArray &recvmsg);

    void clientstate(QAbstractSocket::SocketState state);
protected:

    virtual void incomingConnection(qintptr handle);  //�麯������tcp����ʱ�ᴥ��

signals:
    void stringRecv(QString &str);

    void NotifyClientConnected(int , int );

//    void SendCurriculumID(QString &ip);
public:

    QList<ClientIdIp> clientIdIp_List;

    QList<net_server_socket *> socketlist;

    QByteArray sendbyte;
    QJsonArray jarray;
    QJsonObject jobject;
    QJsonDocument jdocument;

    QMutex socketListmutex;
    QMutex IpIdListmutex;




};
#endif // NET_SERVER_H
