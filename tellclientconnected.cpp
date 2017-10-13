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
    if(times<5)
    {
        QByteArray datagram = "OFFLINECONNECT";
        socket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,1066);
        times++;
        return;
    }
    emit my_stop();

}
