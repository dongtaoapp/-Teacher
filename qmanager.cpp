#include "qmanager.h"
#include <qDebug>

QManager::QManager()
{
    qDebug()<<__FUNCTION__;

    islisten=false;

    tm.start(1000);
    this->managerInit();
    connect(&m_server,SIGNAL(NotifyClientConnected(int,int)),this,SIGNAL(ClientState(int,int)));
   // connect(this,SIGNAL(startspeak()),&m_speak,SLOT(start_audio_to_system()));

    connect(&tm,SIGNAL(timeout()),&test,SLOT(my_send()));
    connect(&test,SIGNAL(my_stop()),&tm,SLOT(stop()));
//    connect(this,SIGNAL(startListen()),&m_listen,SLOT(start_system_audio()));
//    connect(this,SIGNAL(stopListen()),&m_listen,SLOT(stop_sys_audio()));
}
QManager::~QManager()
{
    qDebug()<<__FUNCTION__;
}

void QManager::managerInit()
{
    m_server.setserverlisten(666666);
}
///************��ʦ��speak��ʼ��**************/
void QManager::speakAndlistenInit()
{
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
 //   emit startspeak();
}

void QManager::closeClientWindow()
{
    m_server.allTeach_closeall();
}

void QManager::controllisten(bool listen)
{
    if(listen)
    {
        emit startListen();
    }
    else if (!listen)
    {
        emit stopListen();
    }
}

void QManager::doAllowTalk(QList<int> id_list)
{
   for(int i=0;i<id_list.size();i++)
   {
        qDebug()<<"m_server.clientIdIp_List.size() :"<<m_server.clientIdIp_List.size();
       for(int j=0;j<m_server.clientIdIp_List.size();j++)
       {
            if(id_list.at(i)==m_server.clientIdIp_List.at(j).DeskId.toInt())
            {
               m_server.test(m_server.clientIdIp_List.at(j).DeskIp);
            }
       }
   }
   if(!islisten)
   {
       emit startListen();
       islisten=true;
   }
}

void QManager::startAllTeach(bool cmd)
{
    m_server.startAllTeach(cmd);
}
void QManager::AllTeachAction(QString &action)
{
    m_server.ALLTeachAction(action);
}
void QManager::AllTeachActionDiffItem(QString &ID)
{
    m_server.ALLTeachActionDiffItem(ID);
}
void QManager::AllTeachActionDiffItemDelete(QString &index)
{
    m_server.ALLTeachActionDiffItemDelete(index);
}
void QManager::AllTeachActionDiffItemlOAD()
{
    m_server.ALLTeachActionDiffItemLoad();
}