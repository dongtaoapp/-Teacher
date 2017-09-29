#include "listen.h"
#include "define.h"
#include <qDebug>
#pragma execution_character_set("utf-8")

CG729Decoder::CG729Decoder()
{
    initial();
}

CG729Decoder::~CG729Decoder()
{

}

void CG729Decoder::initial()
{
    va_g729a_init_decoder();
}

void CG729Decoder::decode(unsigned char *src,short *dst,int bad_frame)
{
    va_g729a_decoder(src, dst, bad_frame);
}

listen::listen()
{
    m_thread.start();//线程开始

    //设置声音格式
    QAudioFormat format;
    format.setSampleRate (8000);        //设置采样频率
    format.setChannelCount (1);         //设置通道计数
    format.setSampleSize (16);          //设置样本大小，一般为8或者16
    format.setCodec ("audio/pcm");      //设置编码格式
    format.setSampleType (QAudioFormat::SignedInt);   //设置采样类型
    format.setByteOrder (QAudioFormat::LittleEndian); //设置字节序为小端字节序
    socket = new QUdpSocket(this);
    if(socket->bind(QHostAddress::AnyIPv4, 25000, QUdpSocket::ShareAddress))
    {
        qDebug()<<socket->errorString();
        socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);
        socket->joinMulticastGroup(QHostAddress("224.1.2.3"));//加入组播地址
    }
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyReadSlot()));
    output = new QAudioOutput(format);
    outdevice=Q_NULLPTR;
    this->moveToThread(&m_thread);//加入线程
}

listen::~listen()
{
   output->deleteLater();
   if(outdevice!=Q_NULLPTR)
   {
        outdevice->deleteLater();
   }

   m_thread.requestInterruption();
   m_thread.quit();
   m_thread.wait();
   qDebug()<<__FUNCTION__;
}
bool listen::start_system_audio()
{
  qDebug()<<__FUNCTION__;
  if(outdevice!=Q_NULLPTR)
  {
        return false;
  }
  outdevice=output->start();
   return true;
}
void listen::stop_sys_audio()
{
    qDebug()<<__FUNCTION__;
    output->stop();
    outdevice=Q_NULLPTR;

}
/************对声音进行解码处理 并写入扬声器***************/
void listen::star_listen(QByteArray &byte_array)
{
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
    if(outdevice==Q_NULLPTR)
    {
      //  qDebug()<<__FUNCTION__<<"output == null";
        return;
    }
    for(int i=0;i<byte_array.length()/L_FRAME_COMPRESSED;i++)
    {
        unsigned char srcAudio[L_FRAME_COMPRESSED]={'\0'};
        short dstAudio[L_FRAME]={0};
        memcpy(srcAudio,(unsigned char*)byte_array.data()+i * L_FRAME_COMPRESSED,L_FRAME_COMPRESSED);
        //G729解码
        cg729Decoder.decode(srcAudio,dstAudio,0);
        //short转char
        tempframe.append((char *)dstAudio,L_FRAME * 2);

        if(output&&output->state()!=QAudio::StoppedState&&
                output->state()!=QAudio::SuspendedState)
        {
              int chunks = output->bytesFree()/output->periodSize();
              while (chunks)
              {
                  if (tempframe.length() >= output->periodSize())
                  {
                      //写入到扬声器
                      outdevice->write(tempframe.data(),output->periodSize());
                      tempframe = tempframe.mid(output->periodSize());
                  }
                  else
                  {
                      //写入到扬声器
                      outdevice->write(tempframe);
                      tempframe.clear();
                      break;
                  }
                  --chunks;
              }
         }
    }

}
/** 对声音进行采集**/
void listen::readyReadSlot()
{
    QByteArray datagram;
    while (socket->hasPendingDatagrams())
    {     
           if(socket->pendingDatagramSize()==-1)
           {
               return ;
           }
           datagram.resize(socket->pendingDatagramSize());
           QHostAddress sender;
           quint16 senderPort;
           socket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
           if(datagram.size()>0)
           {
               star_listen(datagram);
           }
     }
}

