#include "qcompareview.h"
#include "ui_qcompareview.h"
#include <qDebug>
#include <QPainter>
#include <QMessageBox>
QCompareView::QCompareView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCompareView)
{
    ui->setupUi(this);
    m_soundNum=0;
    setAutoFillBackground(true);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏

    connect(ui->compareBtn,SIGNAL(clicked(bool)),this,SLOT(onUiCompareBtn()));
    connect(ui->deleteBtn_first,SIGNAL(clicked(bool)),this,SLOT(onUideleteBtnFirst()));
    connect(ui->deleteBtn_second,SIGNAL(clicked(bool)),this,SLOT(onUideleteBtnSecond()));
    connect(ui->empty_btn,SIGNAL(clicked(bool)),this,SLOT(onUiemityBtn()));
    connect(ui->hide_btn,SIGNAL(clicked()),this,SLOT(hide()));

}

QCompareView::~QCompareView()
{
    delete ui;
}

void QCompareView::setEmpityBtnWork(bool work)
{
    ui->empty_btn->setEnabled(work);
}
void QCompareView::addComopareMsg(diffSound &data)
{
  m_soundNum++;
  if(ui->label_first->text().isEmpty())
  {
      ui->label_first->setText(data.m_strSoundName);
      labelData1=data;
      return;
  }
  if(ui->label_second->text().isEmpty())
  {
      ui->label_second->setText(data.m_strSoundName);
      labelData2=data;
      return;
  }
}
void QCompareView::onUiCompareBtn()
{
    if(ui->label_first->text().isEmpty()||ui->label_second->text().isEmpty())
    {
       QMessageBox::information(this,QStringLiteral("信息提示"),QStringLiteral("请选择两个声音才能进行对比"));
    }
    else
    {
        emit CompareBntCilcked(labelData1,labelData2);
    }
}

void QCompareView::onUideleteBtnFirst()
{
    if(!ui->label_first->text().isEmpty())
    {
        ui->label_first->clear();
        m_soundNum--;
        emit deleteDiffSound1(labelData1);
    }
}
void QCompareView::onUideleteBtnSecond()
{
    if(!ui->label_second->text().isEmpty())
    {
        ui->label_second->clear();
        m_soundNum--;
        emit deleteDiffSound2(labelData2);
    }
}
void QCompareView::onUiemityBtn()
{
    if(!ui->label_first->text().isEmpty())
    {
        m_soundNum--;
        ui->label_first->clear();
        emit deleteDiffSound1(labelData1);
    }
    if(!ui->label_second->text().isEmpty())
    {
        ui->label_second->clear();
        m_soundNum--;
        emit deleteDiffSound2(labelData2);
    }
}
void QCompareView::widgetinit()
{
    if(!ui->label_first->text().isEmpty())
    {
        m_soundNum--;
        ui->label_first->clear();
    }
    if(!ui->label_second->text().isEmpty())
    {
        m_soundNum--;
        ui->label_second->clear();
    }
}
void QCompareView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
