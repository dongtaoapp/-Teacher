#include "courseware_widget.h"
#include "ui_courseware_widget.h"
#include "define.h"
#include <qDebug>
#include <QStyleOption>
#include <QPainter>
courseware_widget::courseware_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::courseware_widget)
{
    ui->setupUi(this);
    this->setObjectName("courseware_widget");
    QString str="QPushButton{background-color:#3099e5;color:white;;border-style:none;}"
                "QPushButton:pressed{image:url(:/images/clicked.png)}";
    this->setStyleSheet(str);
    connect(ui->abdomen_T_btn,SIGNAL(clicked(bool)),this,SLOT(on_ABT_cware()));
    connect(ui->ECG_btn,SIGNAL(clicked(bool)),this,SLOT(on_ECG_cware()));
    connect(ui->HT_btn,SIGNAL(clicked(bool)),this,SLOT(on_HS_cware()));
}

courseware_widget::~courseware_widget()
{
    delete ui;
}
void courseware_widget::btnInit()
{
    ui->abdomen_T_btn->setStyleSheet(QString("image:url(:/images/q.png)"));
    ui->HT_btn->setStyleSheet(QString("image:url(:/images/q.png)"));
    ui->ECG_btn->setStyleSheet(QString("image:url(:/images/q.png)"));

}
void courseware_widget::on_ABT_cware()
{
     btnInit();
     ui->abdomen_T_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
     emit cware_btn_id(ID_ABT_CWARE);
}
void courseware_widget::on_HS_cware()
{
    btnInit();
    ui->HT_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
    emit cware_btn_id(ID_HS_CWARE);
}
void courseware_widget::on_ECG_cware()
{
    btnInit();
    ui->ECG_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
    emit cware_btn_id(ID_ECG_CWARE);
}

void courseware_widget::setBtnFoucse(int index)
{
    btnInit();
    switch(index)
    {
    case 0:
        ui->HT_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
        break;
    case 1:
        ui->abdomen_T_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
        break;
    case 2:
        ui->ECG_btn->setStyleSheet(QString("image:url(:/images/clicked.png);border-style:solid;border-left:3px solid white"));
        break;
    default:
        break;
    }
}
void courseware_widget::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
