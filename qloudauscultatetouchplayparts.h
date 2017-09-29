#ifndef QLOUDAUSCULTATETOUCHPLAYPARTS_H
#define QLOUDAUSCULTATETOUCHPLAYPARTS_H
#include "qsoundplayparts.h"
#include <QJsonValue>

class QLoudAuscultateTouchPlayParts:public QSoundPlayParts
{
public:
    QLoudAuscultateTouchPlayParts(bool bLeftTrack,QString strAppPath, bool bIgnoreTrack=false);
protected:
    //��ʼ������
    virtual void InitialSoundPart(HWND hWnd,  QByteArray strSoundInfo,QString &tremble_position,QString &default_sound);
    //��ʼ��������������
    virtual void InitialDiffSoundPart(HWND hWnd,  QByteArray strSoundInfo1,QByteArray strSoundInfo2);
public:
    bool InitialLoadLoudSound(HWND hWnd,  QByteArray strSoundInfo,QString &tremble_position,QString &default_sound);
    bool InitialLoadDiffLoudSound(HWND hWnd,  QByteArray strSoundInfo1,QByteArray strSoundInfo2);
protected:
    //������Դ��
    QString  ReturnSoundName(const QJsonValue& value);
//protected:
//    bool m_strLoudSound;
};

#endif // QLOUDAUSCULTATETOUCHPLAYPARTS_H
