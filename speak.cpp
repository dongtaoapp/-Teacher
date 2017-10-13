#include "speak.h"
#include "define.h"
#include <qDebug>
#include <QAudioFormat>
#pragma execution_character_set("utf-8")

const int BUFFER_SIZE = 4096;

CG729Encoder::CG729Encoder()
{
    initial();
}

CG729Encoder::~CG729Encoder()
{

}

void CG729Encoder::initial()
{
    va_g729a_init_encoder();
}

void CG729Encoder::encode(short *src,unsigned char *dst)
{
    va_g729a_encoder(src, dst);
}

speak::speak()

{
     m_thread.start();
    //����������ʽ
    QAudioFormat format;
    format.setSampleRate (8000);        //���ò���Ƶ��
    format.setChannelCount (1);         //����ͨ������
    format.setSampleSize (16);          //����������С��һ��Ϊ8����16
    format.setCodec ("audio/pcm");      //���ñ����ʽ
    format.setSampleType (QAudioFormat::SignedInt);   //���ò�������
    format.setByteOrder (QAudioFormat::LittleEndian); //�����ֽ���ΪС���ֽ���
    input =  new QAudioInput(format,this);
    SOCKET =new QUdpSocket(this);
    indevice=Q_NULLPTR;
    connect(input,SIGNAL(stateChanged(QAudio::State)),this,SLOT(state(QAudio::State)));
    this->moveToThread(&m_thread);
}

speak::~speak()
{
  input->deleteLater();
  SOCKET->deleteLater();
  indevice->deleteLater();

  m_thread.requestInterruption();
  m_thread.quit();
  m_thread.wait();
  qDebug()<<__FUNCTION__;
}
/** ����Ƶд��IOdevice*/
void speak::start_audio_to_system()
{
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
    if(indevice==Q_NULLPTR)
    {
         indevice= input->start();
    }
    else
    {
        qDebug()<<__FUNCTION__<<"indevice is not null================================";
    }
    connect(indevice,SIGNAL(readyRead()),this,SLOT(on_readyRead()));
}

//ֹͣ��Ƶ���룬��ϵͳ��Դ���롣

void speak::stop_voice_in()
{
    input->stop();
    indevice=Q_NULLPTR;
}

/*
bool speak::setTalkipList(QStringList &ipList)
{
    if(ipList.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"ipList is empty";
        return false;
    }
   speakListmutex.lock();
   m_iplist.clear();
   for(int i=0;i<ipList.size();i++)
   {
       m_iplist.append(ipList.at(i));
   }
   speakListmutex.unlock();
   return true;
}
*/

/** ͨ��UDP���������Ĳ���*/
void speak::start_speak(QByteArray &speak_data)
{
   qint64 aa =SOCKET->writeDatagram(speak_data, QHostAddress("224.1.1.3"), 250000);
//   qDebug()<<__FUNCTION__<<"socket size:"<<aa;
}
/***�Լ��������������д���*********/

void speak::on_readyRead()
{
    short srcAudio[L_FRAME]={0};
    unsigned char dstAudio[L_FRAME_COMPRESSED]={'\0'};
    if (input->error()!=QAudio::NoError)
    {
        qDebug() << "AudioInput Error";
        if(input->error()==QAudio::IOError)
        {
            emit error(QString("IOError"));//��/д��Ƶ�豸ʱ��������
        }
        else if(input->error()==QAudio::UnderrunError)
        {
            emit error(QString("UnderrunError"));//δ֪����
        }
        else if(input->error()==QAudio::OpenError)
        {
            emit error(QString("OpenError"));//�򿪴���
        }
        else if(input->error()==QAudio::FatalError)
        {
            emit error(QString("FatalError"));//�������ɻָ��Ĵ�����Ƶ�豸��ʱ�����á�
        }
        return;
    }

    QByteArray dataBuffer(BUFFER_SIZE,0);
    qint64 len1 = input->bytesReady();

    if (len1 > BUFFER_SIZE)
    {
        qDebug()<<"BUFFER_SIZE too small";
        return;
    }
    qint64 len2 = indevice->read(dataBuffer.data(), len1);

    tempBuffer.append(dataBuffer.data(),len2);

    for(int i=0;i<tempBuffer.length()/(L_FRAME*2);i++)
    {
        //charתshort
        memcpy(srcAudio,tempBuffer.data()+i*L_FRAME*2,L_FRAME*2);
        //����
        cg729Encoder.encode(srcAudio, dstAudio);
        QByteArray frame;
        //reinterpret_cast����ǿ��ת�������ｫunsigned char *ת��Ϊconst char *��
        frame.append(reinterpret_cast<const char*>(dstAudio),L_FRAME_COMPRESSED);
        start_speak(frame);
    }
    tempBuffer.clear();
}

void speak::state(QAudio::State state)
{
  qDebug()<<__FUNCTION__<<state;

}
