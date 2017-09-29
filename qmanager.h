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
    void AllTeachAction(QString &action);
    void AllTeachActionDiffItem(QString &ID);
    void AllTeachActionDiffItemDelete(QString &index);
    void AllTeachActionDiffItemlOAD();
public slots:
    void closeClientWindow();
    void doAllowTalk(QList<int> id_list);
    void speakAndlistenInit();
    void controllisten(bool listen);
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
