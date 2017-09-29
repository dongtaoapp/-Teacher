#ifndef TELLCLIENTCONNECTED_H
#define TELLCLIENTCONNECTED_H
#include <QObject>
#include <QUdpSocket>
class TellClientConnected : public QObject
{
    Q_OBJECT
public:
    TellClientConnected();
    ~TellClientConnected();
private slots:
    void my_send();
signals:
    void my_stop();
private:
    QUdpSocket *socket;
    int times;
};

#endif // TELLCLIENTCONNECTED_H
