#include "setitemview.h"
#include "ui_setitemview.h"
#include "define.h"
#include <qDebug>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
SetItemView::SetItemView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetItemView)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    this->setWindowTitle(QStringLiteral("系统设置选项"));
    reloadTime=0;
    pag1_radiobtn=-1;
    pag2_radiobtn=-1;
    ui->stackedWidget->setCurrentIndex(2);
    configInit = new QSettings(APPPATH, QSettings::IniFormat);
    ReadInit();
    this->Init();
    connect(this,SIGNAL(changPag(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    connect(ui->btn1,SIGNAL(clicked(bool)),this,SLOT(onBtn1()));
    connect(ui->btn2,SIGNAL(clicked(bool)),this,SLOT(onBtn2()));
    connect(ui->btn3,SIGNAL(clicked(bool)),this,SLOT(onBtn3()));
    connect(ui->cancelBtn,SIGNAL(clicked(bool)),this,SLOT(oncancelBtn()));
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(onOkbtn()));
    connect(this,SIGNAL(reloadProcess()),this,SLOT(reload()));

}

SetItemView::~SetItemView()
{
    delete ui;
    delete configInit;
    qDebug()<<__FUNCTION__;
}
void SetItemView::onBtn1()
{
    btnInit();
    ui->btn1->setStyleSheet(QString("QPushButton{color:#4aabe9;background-color:#f6f7fc}"));
    emit changPag(0);
}
void SetItemView::onBtn2()
{
    btnInit();
    ui->btn2->setStyleSheet(QString("QPushButton{color:#4aabe9;background-color:#f6f7fc}"));
    emit changPag(1);
}
void SetItemView::onBtn3()
{
    btnInit();
    ui->btn3->setStyleSheet(QString("QPushButton{color:#4aabe9;background-color:#f6f7fc}"));
    emit changPag(2);
}
void SetItemView::btnInit()
{
     ui->btn1->setStyleSheet(QString("QPushButton{color:;background-color:}"));
     ui->btn2->setStyleSheet(QString("QPushButton{color:;background-color:}"));
     ui->btn3->setStyleSheet(QString("QPushButton{color:;background-color:}"));
}
void SetItemView::ReadInit()
{
    pag1_radiobtn= configInit->value("System_Param/HeartAuscultateType").toInt();
    pag2_radiobtn=configInit->value("System_Param/LoudSoundType").toInt();
    deskNumber=configInit->value("System_Param/deskNumber").toInt();
    webIP=configInit->value("System_Param/WebIP").toString();
}
void SetItemView::Init()
{
    switch(pag1_radiobtn)
    {
    case 1:
        ui->radioButton->setChecked(true);
        break;
    case 0:
        ui->radioButton_2->setChecked(true);
        break;
    default:
        ui->radioButton->setChecked(true);
        break;
    }
    switch(pag2_radiobtn)
    {
    case 1:
        ui->radioButton_3->setChecked(true);
        break;
    case 0:
        ui->radioButton_4->setChecked(true);
        break;
    default:
        ui->radioButton_3->setChecked(true);
        break;
    }
    ui->spinBox->setValue(deskNumber);
    ui->web_ip->setText(webIP);
}
/******写入配置文件*******/
void SetItemView::onOkbtn()
{
    if(pag1_radiobtn==1)
    {
        if(!ui->radioButton->isChecked())
        {
             configInit->setValue("System_Param/HeartAuscultateType","0");
             reloadTime++;
        }
    }
    if(pag1_radiobtn==0)
    {
        if(ui->radioButton->isChecked())
        {
            configInit->setValue("System_Param/HeartAuscultateType","1");
            reloadTime++;
        }
    }
    if(pag2_radiobtn==1)
    {
        if(!ui->radioButton_3->isChecked())
        {
           configInit->setValue("System_Param/LoudSoundType","0");
           reloadTime++;
        }
    }
    if(pag2_radiobtn==0)
    {
        if(ui->radioButton_3->isChecked())
        {
            configInit->setValue("System_Param/LoudSoundType","1");
            reloadTime++;
        }
    }
    if(deskNumber!=ui->spinBox->text().toInt())
    {
        configInit->setValue("System_Param/deskNumber",ui->spinBox->text());
        reloadTime++;
    }
    if(webIP!=ui->web_ip->text())
    {
        configInit->setValue("System_Param/WebIP",ui->web_ip->text());
        reloadTime++;
    }
    if(reloadTime!=0)
    {
        emit pattern(QString("InitChange"));
        emit reloadProcess();
    }
}

void SetItemView::oncancelBtn()
{
    Init();
    this->close();
}

void SetItemView::reload()
{
     this->close();
     QMessageBox::information(this,QStringLiteral("信息提示"),QStringLiteral("配置文件已修改,程序需要重启"));
     qApp->quit();
     QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}
