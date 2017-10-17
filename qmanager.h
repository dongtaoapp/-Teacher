#ifndef QMANAGER_H
#define QMANAGER_H

#include <QObject>
#include "net_server.h"
#include "define.h"
#include "speak.h"
#include "listen.h"
#include "tellclientconnected.h"
#include <QString>
#include <QList>
#include <QTimer>

class QManager : public QObject
{
    Q_OBJECT
public:
    QManager();
    ~QManager();
    void managerInit();
    void startAllTeach(bool cmd);
    void AllTeachActionTab(int tab);
    void AllTeachActionBtn(QString &action);
    void AllTeachActionDiffItem(QString &ID);
    void AllTeachActionDiffItemDelete(QString &index);
    void AllTeachActionDiffItemlOAD();
    void ALLTeachLocalFlash(QString &FileName);
    void ALLTeachLocalCase(QString &ID);
    void ALLTeachWork(QString &work);



public slots:
    void closeClientWindow();
    void doAllowTalk(QList<int> id_list,bool cmd);
    void speakAndlistenInit();
    void controllisten(bool listen);

    void pattern(QString str);
signals:
    void ClientState(int ,int);
    void startListen();
    void stopListen();
    void startspeak();
private:
    net_server m_server;
    speak m_speak;
    listen m_listen;
    QStringList ClientIpList;
    QList<ClientIdIp> m_list;
    QTimer tm;
    TellClientConnected test;
    bool islisten;
};

#endif // QMANAGER_H
