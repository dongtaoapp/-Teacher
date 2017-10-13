#include "talkbackview.h"
#include "ui_talkbackview.h"
#include "define.h"
#include <qDebug>
#include <QVBoxLayout>
#include <QFile>
#include <QPoint>
#include <QAbstractAnimation>
#include <QPainter>
#include <QtCore/qmath.h>
TalkbackView::TalkbackView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalkbackView)
{

    ui->setupUi(this);
    ui->chose_all->setEnabled(false);
    this->setObjectName("TalkbackView");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setModal(false);
    talkback=false;
    quit=true;
    popup=false;
    close_btn=new QPushButton(this);
    close_btn->setObjectName("close_btn");
    close_btn->setGeometry(666,5,30,30);
    ui->top_label->setText(QStringLiteral("     对讲操作"));
    loadqss();

    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    ui->scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scrollArea->setWidgetResizable(true);
    m_tabnum=0;
    scrollArea_widget=new QWidget;
    scrollArea_widget->setObjectName("scrollArea_widget");
    scrollArea_widget->resize(620,250);
    scrollArea_widget->setStyleSheet("QCheckBox {font-size:12px;font-weight:normal}"
                                     "QCheckBox::indicator:checked {image:url(:/images/Check-box--(Checked).png)}"
                                     "QCheckBox::indicator:unchecked {image:url(:/images/Check-box-(hover).png)}");
    connect(ui->chose_all,SIGNAL(stateChanged(int)),this,SLOT(all_chose(int)));
    connect(ui->popup_chex,SIGNAL(stateChanged(int)),this,SLOT(popup_chose(int)));
    connect(ui->quit_btn,SIGNAL(clicked(bool)),this,SLOT(on_quitbtn()));
    connect(ui->allow_btn,SIGNAL(clicked(bool)),this,SLOT(on_allowbtn()));

    connect(ui->stop_btn,SIGNAL(clicked(bool)),this,SLOT(StopTalk()));
    connect(ui->remove_btn,SIGNAL(clicked()),this,SLOT(on_removebtn()));
    connect(close_btn,SIGNAL(clicked()),this,SLOT(close()));
}

TalkbackView::~TalkbackView()
{
     delete ui;
     scrollArea_widget->deleteLater();
     QMapIterator<int,QCheckBox *> iter(testbed_map);
     while(iter.hasNext())
     {
         iter.next();
         delete iter.value();
     }
    qDebug()<<__FUNCTION__;
}

void TalkbackView::loadqss()
{
    QFile file(":/qss/talkwindow.qss");
    if(file.open(QFile::ReadOnly))
    {
      QString str;
      str.prepend(file.readAll());
      this->setStyleSheet(str);
    }
    file.close();
}


void TalkbackView::setTablenum(int num)
{
    QMapIterator<int,QCheckBox *> iter(testbed_map);
    while(iter.hasNext())
    {
        iter.next();
        delete iter.value();
    }
    testbed_map.clear();
    m_tabnum=num;
    tableInit();
}
void TalkbackView::stateInit()
{
    QMapIterator<int, chexbox_state> iter(tab_state_map);
    while(iter.hasNext())
    {
        iter.next();
        if(iter.value()==TBVREQUEST)
        {
          testbed_map.find(iter.key()).value()->setStyleSheet(REQUEST_ICON);
        }
        if(iter.value()==TBVONLINE)
        {
         testbed_map.find(iter.key()).value()->setStyleSheet(ONLINE_ICON);
        }
        if(iter.value()==TBVOFFLINE)
        {
          testbed_map.find(iter.key()).value()->setStyleSheet(OFFLINE_ICON);
        }
    }
}

void TalkbackView::tableInit()
{
    if(m_tabnum==0)
    {
        return;
    }
    if(m_tabnum>12)
    {
        scrollArea_widget->setMinimumSize(600,10000);
    }
    for(int i=1;i<=m_tabnum;i++)
    {
         QCheckBox *box=new QCheckBox(scrollArea_widget);
         box->setLayoutDirection(Qt::RightToLeft);
         box->setText(QString(QStringLiteral("试验台%1 ")).arg(i));
         testbed_map.insert(i,box);
         box->setStyleSheet(OFFLINE_ICON);
         box->resize(CHEXBOX_WIDTH,CHEXBOX_HEIGHT);
         if(i==1)
         {
             box->move(INTERVAL,INTERVAL);
         }
         if(i==2)
         {
             box->move(INTERVAL*2+CHEXBOX_WIDTH,INTERVAL);
         }
         if(i==3)
         {
             box->move(INTERVAL*3+CHEXBOX_WIDTH*2,INTERVAL);
         }
         if(i==4)
         {
             box->move(INTERVAL*4+CHEXBOX_WIDTH*3,INTERVAL);
         }
         if((i-1)%4==0)
         {
             int num=(i-1)/4;
             box->move(INTERVAL,INTERVAL*(num+1)+CHEXBOX_HEIGHT*num);
         }
         if((i-2)%4==0)
         {
             int num=(i-2)/4;
             box->move(INTERVAL*2+CHEXBOX_WIDTH,INTERVAL*(num+1)+CHEXBOX_HEIGHT*num);

         }
         if((i-3)%4==0)
         {
             int num=(i-3)/4;
             box->move(INTERVAL*3+CHEXBOX_WIDTH*2,INTERVAL*(num+1)+CHEXBOX_HEIGHT*num);
         }
         if((i-4)%4==0)
         {
             int num=(i-4)/4;
             box->move(INTERVAL*4+CHEXBOX_WIDTH*3,INTERVAL*(num+1)+CHEXBOX_HEIGHT*num);
         }
    }
   ui->scrollArea->setWidget(scrollArea_widget);
   stateInit();
}
void TalkbackView::all_chose(int chose)
{
    QMapIterator<int,QCheckBox *> iter(testbed_map);
    QMapIterator<int, chexbox_state> iter1(tab_state_map);
    if(chose)
    {

        while(iter1.hasNext())
        {
            iter1.next();
            if(iter1.value()==TBVONLINE)
            {
                testbed_map.find(iter1.key()).value()->setChecked(true);
            }
        }
    }
    else
    {
        while(iter.hasNext())
        {
            iter.next();
            iter.value()->setChecked(false);
         }
    }
}


void TalkbackView::popup_chose(int chose)
{
    if(chose)
    {
        popup=true;
    }
    else
    {
        popup=false;
    }
}




void TalkbackView::on_quitbtn()
{
    if(!quit)
    {
        //执行非静音操作

        emit doquit(true);
        quit=true;
        ui->quit_btn->setText(QStringLiteral("静音"));
        return;
    }
    else if(quit)
    {
        //执行静音操作

        emit doquit(false);
        quit=false;
        ui->quit_btn->setText(QStringLiteral("听取"));
        return;
    }
}

void TalkbackView::on_removebtn()
{

    QMapIterator<int, chexbox_state> iter(tab_state_map);
    while(iter.hasNext())
    {
        iter.next();
        if(iter.value()==TBVREQUEST)
        {
            qDebug()<<__FUNCTION__<<"key :"<<iter.key();
            setTestbedState(iter.key(),ONLINE);
        }
    }
}

void TalkbackView::on_allowbtn()
{
  QList<int > allow_id_list;
  QMapIterator<int,QCheckBox *> iter(testbed_map);
  while(iter.hasNext())
     {
         iter.next();
         chexbox_state m_state= tab_state_map.find(iter.key()).value();
         if(iter.value()->isChecked()&&m_state==TBVONLINE||m_state==TBVREQUEST)
         {
             setTestbedState(iter.key(),TALKING);
             iter.value()->setChecked(false);
             allow_id_list.append(iter.key());
         }
         else
         {
             iter.value()->setChecked(false);
         }
     }
  if(allow_id_list.isEmpty())
  {
    return;
  }
   emit allowTalkList(allow_id_list,true);
   emit changTalkBntIcon();
}

void TalkbackView::StopTalk()
{
    QList<int > allow_id_list;
    QMapIterator<int,QCheckBox *> iter(testbed_map);
    while(iter.hasNext())
       {
           iter.next();
           if(iter.value()->isChecked()&&tab_state_map.find(iter.key()).value()==TBVTALKING)
           {
               setTestbedState(iter.key(),ONLINE);
               iter.value()->setChecked(false);
               allow_id_list.append(iter.key());
           }
           else
           {
               iter.value()->setChecked(false);
           }
       }
    if(allow_id_list.isEmpty())
    {
      return;
    }
    emit allowTalkList(allow_id_list,false);
}

bool TalkbackView::setTestbedState(int id, int state)
{
    if(id>m_tabnum)
    {
        qDebug()<<__FUNCDNAME__<<"id error";
        return false;
    }
    if(state==ONLINE)
    {
        testbed_map.find(id).value()->setStyleSheet(ONLINE_ICON);
        tab_state_map.insert(id,TBVONLINE);
        return true;
    }
    if(state==OFFLINE)
    {
        testbed_map.find(id).value()->setStyleSheet(OFFLINE_ICON);
        tab_state_map.insert(id,TBVOFFLINE);
        return true;
    }
    if(state==REQUEST)
    {
        testbed_map.find(id).value()->setStyleSheet(REQUEST_ICON);
        tab_state_map.insert(id,TBVREQUEST);
        return true;
    }
    if(state==TALKING)
    {
        testbed_map.find(id).value()->setStyleSheet(TALKING_ICON);
        tab_state_map.insert(id,TBVTALKING);
        return true;
    }
}

void TalkbackView::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}
void TalkbackView::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton&&ui->top_label->frameRect().contains(this->xOffset,this->yOffset))
    {
       this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
    }
}
void TalkbackView::paintEvent(QPaintEvent *event)
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

