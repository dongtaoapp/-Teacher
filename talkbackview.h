#ifndef TALKBACKVIEW_H
#define TALKBACKVIEW_H

#include <QDialog>
#define CHEXBOX_WIDTH 100
#define CHEXBOX_HEIGHT 20
#define INTERVAL 40//chexbox间的间隔

#define ONLINE_ICON  "QCheckBox{image:url(:/images/testbed_connected_icon.png);}"
#define OFFLINE_ICON "QCheckBox{image:url(:/images/testbed_disconnect_icon.png)}"
#define REQUEST_ICON "QCheckBox{image:url(:/images/raisehands_icon.png);color:#1abc9c}"
#define TALKING_ICON "QCheckBox{image:url(:/images/Talking.png);color:#1abc9c}"
#include <QList>
#include <QCheckBox>
#include <QWidget>
#include <QMap>
#include<QMapIterator>
#include <QIcon>
#include <QPushButton>
#include <QMouseEvent>
#include <QPropertyAnimation>
typedef QMap<int,QCheckBox *> m_map;

namespace Ui {
class TalkbackView;
}

class TalkbackView : public QDialog
{
    Q_OBJECT
public:

    enum chexbox_state{
        TBVONLINE=0,
        TBVOFFLINE=1,
        TBVREQUEST=2,
        TBVTALKING
    };
public:
    explicit TalkbackView(QWidget *parent = 0);
    ~TalkbackView();
    void loadqss();

    void stateInit();
public slots:

    void all_chose(int chose);

    void popup_chose(int chose);

    void on_quitbtn();

    void on_removebtn();

    bool setTestbedState(int id,int state);//试验台状态函数

    void on_allowbtn();

    void StopTalk();
signals:
   // void stop_talkback();

    void StartOrStopTalk(bool);//开始结束对讲信号

    void allowTalkList(QList<int>,bool );

    void doquit( bool );

    void changTalkBntIcon();
public :
    void setTablenum(int num);
    void tableInit();


protected:
    void mousePressEvent (QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
public :
     int m_tabnum;
     bool popup;//学生请求弹出标记
private:
    Ui::TalkbackView *ui;

    m_map testbed_map;

    QMap<int,chexbox_state> tab_state_map;

    QWidget *scrollArea_widget;
    QPushButton *close_btn;
    bool talkback;
    bool quit;
    int xOffset,yOffset;

};

#endif // TALKBACKVIEW_H
