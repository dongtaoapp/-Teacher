#include "net_server.h"
#include <qDebug>
#include <QMapIterator>
#include <QSettings>
extern bool Global_Synchronous;
net_server_socket::net_server_socket()
{
    qDebug()<<__FUNCTION__;
    connect(this,SIGNAL(readyRead()),this,SLOT(onreadyRead()));
    connect(this,SIGNAL(disconnected()),this,SLOT(ondisconnected()));
}

net_server_socket::~net_server_socket()
{
  this->deleteLater();
}

qintptr net_server_socket::returnDescriptor()
{
    return socketDescriptor();
}
void net_server_socket::onreadyRead()
{
  QByteArray recvMsg=this->readAll();
  emit signal_recv(recvMsg);
}
void net_server_socket::ondisconnected()
{
    emit signal_descriptor(this->socketDescriptor());
}

net_server::net_server(QObject *parent):
    QTcpServer(parent)
{
    qDebug()<<__FUNCTION__;
}
net_server::~net_server()
{

    for(int i=0;i<socketlist.size();i++)
    {
        socketlist.at(i)->deleteLater();
    }
    this->deleteLater();
    qDebug()<<__FUNCTION__;
}
bool net_server::setserverlisten(quint16 port)
{
    if(port<0)
    {
        return false;
    }
    return listen(QHostAddress::AnyIPv4,port);
}
void net_server::incomingConnection(qintptr handle)  //虚函数，有tcp请求时会触发
{

    net_server_socket *socket = new net_server_socket;

    if(!socket->setSocketDescriptor(handle))
    {
        qDebug()<<socket->errorString();
        socket->deleteLater();
        return;
    }
    QSettings *readconfig=new QSettings(APPPATH, QSettings::IniFormat);
    QString str=readconfig->value("System_Param/HeartAuscultateType").toString()+
            QString(":")+readconfig->value("System_Param/LoudSoundType").toString();
    delete readconfig;
    if(Global_Synchronous)
    {
        str +=QString(":Synchronous");
    }
    if(!Global_Synchronous)
    {
        str +=QString(":NOSynchronous");
    }
    socket->write(TellClientConnectedSuucess(str));
    socketListmutex.lock();
    socketlist.append(socket);
    socketListmutex.unlock();

    connect(socket,SIGNAL(signal_recv(QByteArray&)),this,SLOT(onRecvmsg(QByteArray&)));
    connect(socket,SIGNAL(signal_descriptor(qintptr)),this,SLOT(ondisconnected(qintptr)));
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(clientstate(QAbstractSocket::SocketState)));
}

void net_server::onRecvmsg(QByteArray &recvmsg)
{
    QJsonParseError simp_json_error;

    QJsonDocument jdocument =QJsonDocument::fromJson(recvmsg,&simp_json_error);

    if(simp_json_error.error==QJsonParseError::NoError)
    {
        QJsonObject object=jdocument.object();
        if(object.isEmpty())
        {
            return;
        }

         QString type=object.value("Type").toString();
         QString cmd=object.value("cmd").toString();
         QString data=object.value("data").toString();
         qDebug()<<__FUNCTION__<<type<<cmd<<data;
         if(type==QString("string"))
         {
            if(cmd=="DeskID")
            {
                ClientIdIp info;
                info.DeskId=data.section(":",0,0);
                info.DeskIp=data.section(":",1,1);
                qDebug()<<__FUNCTION__<<QString(QStringLiteral("有学生机连接成功该学生机信息实验台ID：%1 学生机IP:%2"))
                          .arg(data.section(":",0,0))
                          .arg(data.section(":",1,1));
                IpIdListmutex.lock();
                clientIdIp_List.append(info);
                IpIdListmutex.unlock();
                emit NotifyClientConnected(data.section(":",0,0).toInt(),ONLINE);

//                /*******发送当前选择的课程号*******/
//                emit SendCurriculumID(data.section(":",1,1));
            }
            else if(cmd=="REQUESTTALK")
            {
               emit NotifyClientConnected(data.toInt(),REQUEST);
            }

         }
    }
    else
    {
        qDebug()<<simp_json_error.errorString();
    }
}

/**客户端socket断开处理**/
void net_server::ondisconnected(qintptr descriptor)
{
    int deskID=-1;
    socketListmutex.lock();
    for(int i=0;i<socketlist.size();i++)
    {
        if(socketlist.at(i)->socketDescriptor()==descriptor)
        {
          qDebug()<<socketlist.at(i)->peerAddress().toString();
          IpIdListmutex.lock();
          for(int j=0;j<clientIdIp_List.size();j++)
          {
                if(clientIdIp_List.at(j).DeskIp==socketlist.at(i)->peerAddress().toString())
                {
                    qDebug()<<__FUNCTION__<<QString(QStringLiteral("试验台号为:%1 试验台IP为%2的学生机断开连接"))
                              .arg(clientIdIp_List.at(j).DeskId)
                              .arg(clientIdIp_List.at(j).DeskIp);
                    deskID=clientIdIp_List.at(j).DeskId.toInt();
                    clientIdIp_List.removeAt(j);
                    IpIdListmutex.unlock();
                }

          }
          socketlist.at(i)->deleteLater();
          socketlist.removeAt(i);
          socketListmutex.unlock();
      }
  }
  qDebug()<<"deskID:"<<deskID;
  emit NotifyClientConnected(deskID,OFFLINE);
  qDebug()<<"socketlist size"<<socketlist.size();
}


void net_server::clientstate(QAbstractSocket::SocketState state)
{
   qDebug()<<__FUNCTION__<<state;
}

void net_server::sendMsgtoClient(QByteArray &msg)
{
    if(msg.isEmpty())
    {
         qDebug()<<__FUNCTION__<<"msg size null";
        return ;
    }
    socketListmutex.lock();
    if(socketlist.size()==0)
    {
        qDebug()<<__FUNCTION__<<"socketlist size 0";
        socketListmutex.unlock();
        return ;
    }
    for(int i=0;i<socketlist.size();i++)
    {
        if(socketlist.at(i)->write(msg)!=msg.size())
        {
            continue;
        }
    }
 socketListmutex.unlock();
}

QByteArray net_server::TellClientConnectedSuucess(QString &str)
{
    jobject.insert("Type",QString("string"));
    jobject.insert("cmd","CLIENTCONNECTEDSUCCESS");
    jobject.insert("data",str);
    jdocument.setObject(jobject);
    return jdocument.toJson(QJsonDocument::Compact);
}

void net_server::sendString(QString &str)
{
  jobject.insert("Type",QString("string"));
  jobject.insert("cmd",QString("NULL"));
  jobject.insert("data",str);
  jdocument.setObject(jobject);

  sendbyte=jdocument.toJson(QJsonDocument::Compact);
  sendMsgtoClient(sendbyte);
  sendbyte.clear();

}
/*
 * json 格式 type cmd data
 * type: flash  talk exam train auscultar closePC string play
 */

void net_server::startAllTeach(bool cmd)
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd","control");
    jobject.insert("data",cmd);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}
//------action tabcurrentID:BtnID
void net_server::ALLTeachActionTab(int tab)
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd",QString("Tab"));
    jobject.insert("data",tab);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();

}
void net_server::ALLTeachActionBtn(QString &action)
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd",QString("action"));
    jobject.insert("data",action);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();

}
void net_server::ALLTeachActionDiffItem(QString &ID)
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd",QString("actionDiffItem"));
    jobject.insert("data",ID);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();

}
void net_server::ALLTeachActionDiffItemDelete(QString index)
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd",QString("actionDiffItemDelete"));
    jobject.insert("data",index);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}
void net_server::ALLTeachActionDiffItemLoad()
{
    jobject.insert("Type",QString("Synchronocus"));
    jobject.insert("cmd",QString("LoadSound"));
    jobject.insert("data","NULL");
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}
/*************flash 相关函数****************/
void net_server::ALLTrachLocalFlash(QString &flashName)
{
    jobject.insert("Type",QString("flash"));
    jobject.insert("cmd",QString("LOCALFlash"));
    jobject.insert("data",flashName);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();

}
void net_server::ALLTeachLocalCase(QString &ID)
{
    jobject.insert("Type",QString("flash"));
    jobject.insert("cmd",QString("LOCALCase"));
    jobject.insert("data",ID);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}

#if 0
void net_server::allTeach_courseware(QString &flashpath)
{
   if(flashpath.isEmpty())
   {
       return;
   }
   jobject.insert("Type",QString("flash"));
   jobject.insert("cmd",QString("NULL"));
   jobject.insert("data",flashpath);
   jdocument.setObject(jobject);

   sendbyte=jdocument.toJson(QJsonDocument::Compact);
   sendMsgtoClient(sendbyte);
   sendbyte.clear();
}
#endif
void net_server::ALLTeachWork(QString &work)
{
    jobject.insert("Type",QString("WORK"));
    jobject.insert("cmd",work);
    jobject.insert("data",QString("NULL"));
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}

void net_server::ALLTeacherPatter(QString patter)
{
    jobject.insert("Type",QString("Patter"));
    jobject.insert("cmd",patter);
    jobject.insert("data",QString("NULL"));
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}

void net_server::ControlTalk(QString ip,bool order)
{
    jobject.insert("Type",QString("talk"));
    jobject.insert("cmd",order);
    jobject.insert("data","null");
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    socketListmutex.lock();
    for(int i=0;i<socketlist.size();i++)
    {
          if(socketlist.at(i)->peerAddress().toString()==ip)
          {
              if(socketlist.at(i)->write(sendbyte)!=sendbyte.size())
              {
                  continue;
              }
         }
    }
    socketListmutex.unlock();
    sendbyte.clear();
}

//------------------------训练相关的函
void net_server::allTeach_train(bool cmd,int train_id)
{
    qDebug()<<train_id;
    QString string_train_id =QString::number(train_id,10);
    jobject.insert("Type",QString("train"));
    jobject.insert("cmd",cmd);
    jobject.insert("data",string_train_id);
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}
//-------------------考试相关函数
void net_server::allTeach_exam(bool cmd,int exam_id)
{
   qDebug()<<exam_id;
   QString string_exam_id =QString::number(exam_id,10);
   jobject.insert("Type",QString("exam"));
   jobject.insert("cmd",cmd);
   jobject.insert("data",string_exam_id);
   jdocument.setObject(jobject);
   sendbyte=jdocument.toJson(QJsonDocument::Compact);
   sendMsgtoClient(sendbyte);
   sendbyte.clear();
}
//---------------------听诊相关函数
void net_server::allTeach_auscultar(bool cmd)
{
    jobject.insert("Type",QString("auscultar"));
    jobject.insert("cmd",cmd);
    jobject.insert("data",QString("NULL"));
    jdocument.setObject(jobject);
    sendbyte=jdocument.toJson(QJsonDocument::Compact);
    sendMsgtoClient(sendbyte);
    sendbyte.clear();
}
//-------------关闭学生电脑
void net_server::allTeach_closeall()
{
  jobject.insert("Type",QString("closePC"));
  jobject.insert("cmd",QString("NULL"));
  jobject.insert("data",QString("NULL"));
  jdocument.setObject(jobject);
  sendbyte=jdocument.toJson(QJsonDocument::Compact);

  sendMsgtoClient(sendbyte);
  sendbyte.clear();
}
