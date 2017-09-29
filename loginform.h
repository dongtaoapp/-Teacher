#ifndef LOGINFORM_H
#define LOGINFORM_H
#include "m_ftp_manager.h"
#include "qdatabase.h"
#include <QDialog>
#include <QLabel>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMovie>
typedef struct userinfo
{
    QString name;
    QString pwd;
    bool remember;
}userinfo;

class serialPortForm :public QListWidget
{
    Q_OBJECT
public:
    serialPortForm(QWidget *parent=Q_NULLPTR);
    ~serialPortForm();
    void setListWidgetHeight(int num);
private:

};

class setBtnForm :public QDialog
{
    Q_OBJECT
public:
   setBtnForm(QWidget *patent=Q_NULLPTR);
   ~setBtnForm();
   void formInit();
private slots:
   void onPortformItemClicked(QListWidgetItem *item);
protected:
   void paintEvent(QPaintEvent *event);
signals:
   void portName(QString &portname);//发送选择得串口名称
private:
   QLabel *topLabel;
   serialPortForm *portForm;

};




/*******登录界面************/
namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    void show_login_name();

    void showInit();

    void windowInit();//窗口初始化
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:
    void m_close();
    void CheckUser(QString name,QString pw);
    void downLoadavantar(QString argc1, QString argc2);

     void loginsuccess(QString &name,QString &headimage);
public slots:
     void slot_on_login_btn_cliced();
     void slot_set_btn();
     void dologin(m_ftp_manager::LOGINSTATE state,QString headpic);


private slots:
     void on_box1_currentIndexChanged(const QString &arg1);

private:

    Ui::LoginForm *ui;
    bool ischeck;
    bool btn_check;
    QString avntar;

    setBtnForm *portWindow;
    QDataBase m_db;
    m_ftp_manager loginmanager;
    QList<loginInfo> infolist;
    QMovie *loadingmove;
    QThread thread;
};

#endif // LOGINFORM_H
