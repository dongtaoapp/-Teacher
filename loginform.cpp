#include "loginform.h"
#include "ui_loginform.h"
#include "define.h"
#include <qDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QListWidgetItem>
#include <QPainter>
#include <QFile>
#include <QtCore/qmath.h>
#include <QSettings>
#include <QMessageBox>
#include <QFileInfo>
/*******串口**********/
serialPortForm::serialPortForm(QWidget *parent):
    QListWidget(parent)
{
   this->insertItem(0,QStringLiteral("串口选择设置"));
   int i=1;
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
   {
           this->insertItem(i,info.portName());
           this-> setFocusPolicy(Qt::NoFocus);
           i++;
   }
   setListWidgetHeight(i);
}

serialPortForm::~serialPortForm()
{

  this->deleteLater();
}
void serialPortForm::setListWidgetHeight(int num)
{
    this->resize(234,32*num);
}


/*******串口界面*************/
setBtnForm::setBtnForm(QWidget *parent):
    QDialog(parent)
{
     this->setAttribute(Qt::WA_TranslucentBackground);


  this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);//隐藏标题栏

   portForm=new serialPortForm(this);
   topLabel=new QLabel(this);
   this->resize(244,portForm->height()+15);
   formInit();
   connect(portForm,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onPortformItemClicked(QListWidgetItem*)));


}
setBtnForm::~setBtnForm()
{

  qDebug()<<__FUNCTION__;
}
void setBtnForm::formInit()
{
  topLabel->resize(244,10);
  topLabel->move(0,0);
  topLabel->setStyleSheet("border-style:solid;background-image:url(:/images/background.png)");
  portForm->move(5,10);
}

void setBtnForm::onPortformItemClicked(QListWidgetItem *item)
{
   QString name=item->text();
   if(name==QStringLiteral("串口选择设置"))
   {
      return;
   }
   emit portName(name);
   QSettings *configIniWrite = new QSettings(APPPATH, QSettings::IniFormat);
   configIniWrite->setValue("System_Param/Comm",name);
   delete configIniWrite;
   this->close();

}
void setBtnForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    /***********画背影**************/
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }

}



/**********登陆界面************/
LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
     qDebug()<<__FUNCTION__<<QThread::currentThreadId();
    ui->setupUi(this);
    ischeck=false;
    btn_check=false;
    avntar=QCoreApplication::applicationDirPath()+QString("/Avatar/%1");
    this->setObjectName("LoginForm");
    portWindow=new setBtnForm(this);
    portWindow->hide();
    loadingmove=new QMovie(QCoreApplication::applicationDirPath()+QString("/Avatar/loading.gif"));
    ui->loading_label->setMovie(loadingmove);
    windowInit();
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);//隐藏标题栏
    ui->box1->setEditable(true);
    ui->box1->setView(new QListView());
    QLineEdit *lineedit= ui->box1->lineEdit();
    lineedit->setPlaceholderText(QStringLiteral("用户名"));
    ui->pwdedit->setPlaceholderText(QStringLiteral("请输入密码"));
    ui->pwdedit->setEchoMode(QLineEdit::Password);
    infolist=m_db.teacherInfo();
    show_login_name();

    connect(ui->set_btn,SIGNAL(clicked()),portWindow,SLOT(show()));
    connect(ui->log_btn,SIGNAL(clicked(bool)),this,SLOT(slot_on_login_btn_cliced()));
    connect(this,SIGNAL(CheckUser(QString, QString)),&loginmanager,SLOT(Login(QString,QString)));
    connect(this,SIGNAL(downLoadavantar(QString, QString)),&loginmanager,SLOT(downloadfile(QString,QString)));
    connect(&loginmanager,SIGNAL(loginstate(m_ftp_manager::LOGINSTATE,QString)),this,SLOT(dologin(m_ftp_manager::LOGINSTATE,QString)));
}

LoginForm::~LoginForm()
{
    if(loadingmove!=Q_NULLPTR)
    {
        delete loadingmove;
    }
    delete ui;
    qDebug()<<__FUNCTION__;
}
void LoginForm::windowInit()
{
    this->resize(764,339);
    portWindow->move(530,21);
}



void LoginForm::slot_on_login_btn_cliced()
{
    if(ui->pwdedit->text().isEmpty()||ui->box1->currentText().isEmpty())
    {
        QMessageBox::warning(this,QStringLiteral("错误提示"),QStringLiteral("请输入密码"),QMessageBox::Yes);
        return;
    }
    ui->box1->setEnabled(false);
    ui->pwdedit->setEnabled(false);
    ui->set_btn->setEnabled(false);
    ui->log_btn->hide();
    ui->checkBox->hide();
    ui->loading_label->show();
    loadingmove->start();
    thread.start();
    loginmanager.moveToThread(&thread);
    emit CheckUser(ui->box1->currentText(),ui->pwdedit->text());
}
void LoginForm::showInit()
{
    loadingmove->stop();
    ui->loading_label->hide();
    ui->box1->setEnabled(true);
    ui->pwdedit->setEnabled(true);
    ui->set_btn->setEnabled(true);
    ui->log_btn->show();
    ui->checkBox->show();
}

void LoginForm::dologin(m_ftp_manager::LOGINSTATE state, QString headpic)
{
  loginInfo info;
  info.name=ui->box1->currentText();
  info.pw=ui->pwdedit->text();
  info.Rbpw=ui->checkBox->isChecked();
  QFileInfo file(headpic);
  info.HeadImage=file.fileName();
  switch(state)
  {
    case m_ftp_manager::LOGINSUCCESS:
        if(infolist.isEmpty())
        {
            qDebug()<<__FUNCTION__<<"first login success";
            emit downLoadavantar(headpic,avntar+file.fileName());
            m_db.insertInfo(info);
             return;
        }
        for(int i=0;i<infolist.size();i++)
        {
            if(ui->box1->currentText()==infolist.at(i).name)
            {
                m_db.updateInfo(info);
                if(infolist.at(i).HeadImage!=file.fileName())
                {
                    qDebug()<<__FUNCTION__<<"Avatar is changed!";
                    emit downLoadavantar(headpic,avntar+file.fileName());
                }
            }
            else
            {
                qDebug()<<__FUNCTION__<<"new Login success!";
                emit downLoadavantar(headpic,avntar+file.fileName());
                m_db.insertInfo(info);
            }
        }
            emit loginsuccess(ui->box1->currentText(),file.fileName());
            delete loadingmove;
            loadingmove= Q_NULLPTR;
            thread.requestInterruption();
            thread.quit();
            thread.wait();
      break;
    case m_ftp_manager::NAMEPWERROR:
        QMessageBox::information(this,QStringLiteral("登陆提醒"),QStringLiteral("用户名或密码错误"),QMessageBox::Yes);
        showInit();
      break;
    case  m_ftp_manager::NONAME:
        QMessageBox::information(this,QStringLiteral("登陆提醒"),QStringLiteral("用户名不存在"),QMessageBox::Yes);
        showInit();
      break;
    case  m_ftp_manager::UNKNOWERROR:
        QMessageBox::information(this,QStringLiteral("登陆提醒"),QStringLiteral("未知错误，可能Web服务器出错"),QMessageBox::Yes);
        showInit();
      break;
  }
}

void LoginForm::show_login_name()
{
    if(infolist.isEmpty())
    {
        qDebug()<<"is emipty";
        return;
    }
    for(int i=0;i<infolist.size();i++)
    {
        ui->box1->insertItem(i,infolist.at(i).name);
    }

}

void LoginForm::on_box1_currentIndexChanged(const QString &arg1)
{
    if(infolist.isEmpty())
    {
        return;
    }
    ui->pwdedit->clear();
    for(int i=0;i<infolist.size();i++)
    {
        if(infolist.at(i).name==arg1)
        {
            qDebug()<<infolist.at(i).Rbpw;
            ui->checkBox->setChecked(infolist.at(i).Rbpw);
            if(infolist.at(i).Rbpw)
            {
                ui->pwdedit->setText(infolist.at(i).pw);
            }
        }
    }
}

/*********设置按钮界面**********/
void LoginForm::slot_set_btn()
{     if(!btn_check)
      {
        portWindow->show();
        btn_check=true;
        return;
      }
     else if(btn_check)
     {
        portWindow->close();
        btn_check=false;
        return;
     }
}

/***********界面相关事件************/
void LoginForm::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    btn_check=false;
    portWindow->close();

}
void LoginForm::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
