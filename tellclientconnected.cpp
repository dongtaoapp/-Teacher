#include "tellclientconnected.h"
#include <QByteArray>
TellClientConnected::TellClientConnected()
{
    qDebug()<<__FUNCTION__;
    socket=new QUdpSocket;
    times=0;
}
TellClientConnected::~TellClientConnected()
{
      qDebug()<<__FUNCTION__;
      delete socket;
}
void TellClientConnected::my_send()
{
    if(times<30)
    {
      QByteArray datagram="CONNECT_TEACHER";
      int cc=  socket->writeDatagram(datagram,QHostAddress::Broadcast,1066);
//        qDebug()<<__FUNCTION__<<cc;
        times++;
        return;
    }
    emit my_stop();

}
