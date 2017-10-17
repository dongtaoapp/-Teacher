#ifndef QMAXWIDGET_H
#define QMAXWIDGET_H
#include <QWidget>
#include <QAxWidget>

class QMAxWidget : public QAxWidget
{
       Q_OBJECT
public:
    QMAxWidget(QWidget *parent=0);
    ~QMAxWidget(){;}
    void Init();
signals:
    void FSCommand(QString,QString);
public:
    void loadFlash(QString &path);
    void StartPlay();
    void PausePlay();
};

#endif // QMAXWIDGET_H
