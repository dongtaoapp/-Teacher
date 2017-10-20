#include "qchosecurriculumview.h"
#include <qDebug>
#include <QPainter>
#include <QStyleOption>
#include <QFile>
#include <QMapIterator>
#include <QMessageBox>
#include <QtCore/qmath.h>
CurriculumItem::CurriculumItem(QWidget *parent):
    QWidget(parent)
{
    this->setObjectName("CurriculumItem");
    this->resize(CurriculumItemWidth,CurriculumItemHeight);
    this->setAttribute(Qt::WA_TranslucentBackground);
    clicked=false;
    itemSetInit();
}
CurriculumItem::~CurriculumItem()
{

}
void CurriculumItem::itemSetInit()
{
   CurriculumName=new QLabel(this);
   CurriculumName->setObjectName("name_label");
   CurriculumName->setGeometry(0,CurriculumItemHeight/4,CurriculumItemWidth,CurriculumItemHeight/4);

   CurriculumTime=new QLabel(this);
   CurriculumTime->setObjectName("tiem_label;");
   CurriculumTime->setGeometry(0,CurriculumItemHeight/4*2+5,CurriculumItemWidth,CurriculumItemHeight/4);
}
void CurriculumItem::setCurriculumMsg(ClassScheduleData Data)
{
    CurriculumName->setText(Data.ScheduleName);
    CurriculumTime->setText(Data.ScheduleTime);
    m_data=Data;
}
void CurriculumItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
         emit m_clicked(true);
    }
}
void CurriculumItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QChoseCurriculumView::QChoseCurriculumView(QWidget *parent):
    QDialog(parent)
{
  num=0;

  chosedBtn=Q_NULLPTR;

  this->resize(699,455);
  this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
  this->setAttribute(Qt::WA_TranslucentBackground);
  windowInit();
  loadqss();
  connect(close_btn,SIGNAL(clicked(bool)),this,SLOT(close()));
  connect(ok_btn,SIGNAL(clicked(bool)),this,SLOT(onOkbnt()));
  connect(cancel_btn,SIGNAL(clicked(bool)),this,SLOT(onCancelBtn()));
}

QChoseCurriculumView::~QChoseCurriculumView()
{
    delete CurriculumWidget;
    qDebug()<<__FUNCTION__;
}

void QChoseCurriculumView::windowInit()
{
    CurriculumWidget=new QWidget;
    CurriculumWidget->resize(CurriculumItemWidth+40,CurriculumItemHeight*4);
    CurriculumWidget->setObjectName("CurriculumWidget");
    CurriculumScrollArea=new QScrollArea(this);
    CurriculumScrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    CurriculumScrollArea->setWidgetResizable(true);
    CurriculumScrollArea->setGeometry(50,100,CurriculumItemWidth+50,CurriculumItemHeight*4);
    top_label=new QLabel(this);
    top_label->setObjectName("top_label");
    top_label->setText(QStringLiteral("     选择课程内容"));
    top_label->setGeometry(10,5,669,39);

    title_label=new QLabel(this);
    title_label->setGeometry(50,80,83,14);
    title_label->setText(QStringLiteral("进入课程内容"));

    close_btn=new QPushButton(this);
    close_btn->setCursor(Qt::PointingHandCursor);
    close_btn->setObjectName("close_btn");
    close_btn->setGeometry(659,5,30,39);

    ok_btn=new QPushButton(this);
    ok_btn->setText(QStringLiteral("确定"));
    ok_btn->setObjectName("ok_btn");
    ok_btn->setCursor(Qt::PointingHandCursor);
    ok_btn->setGeometry(200,400,103,34);

    cancel_btn=new QPushButton(this);
    cancel_btn->setText(QStringLiteral("取消"));
    cancel_btn->setObjectName("cancel_btn");
    cancel_btn->setCursor(Qt::PointingHandCursor);
    cancel_btn->setGeometry(400,400,103,34);

}

void QChoseCurriculumView::loadqss()
{
    QFile file(":/qss/CurriculumView.qss");
    if(file.open(QFile::ReadOnly))
    {
      QString str;
      str.prepend(file.readAll());
      this->setStyleSheet(str);
    }
    file.close();


}

void QChoseCurriculumView::addCurriculum(ClassScheduleData &data)
{
//  CurriculumMsg_list.append(data);
//  setPosition();
    m_data=data;
    setPosition();
}

void QChoseCurriculumView::setPosition()
{

   if(num>4)
   {
       CurriculumWidget->setMinimumSize(CurriculumItemWidth+30,5000);
   }

      QRadioButton *btn=new QRadioButton(CurriculumWidget);
      btn->setCursor(Qt::PointingHandCursor);
      btn->setGeometry(0,15+num*60,14,14);
      CurriculumItem *item=new CurriculumItem(CurriculumWidget);
      item->setCurriculumMsg(m_data);
      item->move(20,num*60);
      item_map.insert(btn,item);
      connect(item,SIGNAL(m_clicked(bool)),btn,SLOT(setChecked(bool)));
      num++;
      CurriculumScrollArea->setWidget(CurriculumWidget);
}


void QChoseCurriculumView::onOkbnt()
{
    QMapIterator<QRadioButton *, CurriculumItem *> iter(item_map);
    while(iter.hasNext())
    {
        iter.next();
        if(iter.key()->isChecked())
        {
             if(iter.key()==chosedBtn)
             {
                  QMessageBox::information(this,QStringLiteral("选择提示"),QString(QStringLiteral("当前正在进行%1课程"))
                 .arg(iter.value()->ItemData().ScheduleName));
                 return;
             }
            this->close();
            chosedBtn=iter.key();
            emit CLNum(iter.value()->ItemData());
        }
    }
}
void QChoseCurriculumView::onCancelBtn()
{
    if(chosedBtn==Q_NULLPTR)
    {
        this->close();
        QMapIterator<QRadioButton *, CurriculumItem *> iter(item_map);
        while(iter.hasNext())
        {
            iter.next();
            iter.key()->setCheckable(false);
            iter.key()->setCheckable(true);
        }

    }
    if(chosedBtn!=Q_NULLPTR)
    {
        chosedBtn->setChecked(true);
        this->close();
    }

    emit m_close();
}
void QChoseCurriculumView::setClassScheduleChecked(QString &ID)
{
    QMapIterator<QRadioButton *, CurriculumItem *> iter(item_map);
    while(iter.hasNext())
    {
       if(iter.value()->ItemData().ScheduleID==ID)
       {
           iter.key()->setChecked(true);
       }
    }
}
void QChoseCurriculumView::closeEvent(QCloseEvent *)
{
    onCancelBtn();
    emit m_close();
}
void QChoseCurriculumView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    /**********画背影**********/
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
void QChoseCurriculumView::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}
void QChoseCurriculumView::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton&&top_label->frameRect().contains(this->xOffset,this->yOffset))
    {
       this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
    }
}











