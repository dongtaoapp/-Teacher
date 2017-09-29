#ifndef LISTEN_H
#define LISTEN_H

#include <QObject>
#include <QIODevice>
#include <QAudioFormat>
#include <QUdpSocket>
#include <QAudioOutput>
#include <QThread>

extern "C"
{
 #include "va_g729a.h"
}        

class CG729Decoder
{
public:
    CG729Decoder();
    ~CG729Decoder();
    void decode(unsigned char *src,short *dst,int bad_frame);

private:
    void initial();

};
class listen: public QObject
{
    Q_OBJECT
public:
     listen();
    ~listen();
public slots:


    bool start_system_audio();//¿ªÊ¼listen

    void stop_sys_audio();//Í£Ö¹listen

    void readyReadSlot();

    void star_listen(QByteArray &byte_array);

signals:
  void  signalSetport();
private:
    QIODevice *outdevice;
    QAudioOutput *output;
    QUdpSocket *socket;
    CG729Decoder cg729Decoder;
    QByteArray tempframe;

    QByteArray thread_byte;

    QThread m_thread;
};

#endif // LISTEN_H
