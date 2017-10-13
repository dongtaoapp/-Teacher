#include "auscultation_widget.h"
#include "ui_auscultation_widget.h"
#include "define.h"
#include <QStyleOption>
#include <QPainter>
#include <qDebug>
auscultation_widget::auscultation_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auscultation_widget)
{
    ui->setupUi(this);
    this->setObjectName("auscultation_widget");
    QString str="QPushButton{background-color:#3099e5;color:white;border:none;}"
                "QWidget{border:none}";
    ui->BS_btn->setFlat(true);
    ui->HS_bt->setFlat(true);
    this->setStyleSheet(str);
    connect(ui->HS_bt,SIGNAL(clicked(bool)),this,SLOT(on_HS_btn()));
    connect(ui->BS_btn,SIGNAL(clicked(bool)),this,SLOT(on_BS_btn()));
}

auscultation_widget::~auscultation_widget()
{
    delete ui;
}
void auscultation_widget::btnInit()
{
    ui->BS_btn->setStyleSheet(QString("image:url(:/images/a.png)"));
    ui->HS_bt->setStyleSheet(QString("image:url(:/images/a.png)"));
}
void auscultation_widget::on_BS_btn()
{
    btnInit();
    ui->BS_btn->setStyleSheet(QString("image:url(:/images/clicked.png)"));
    emit aut_btn_id(ID_BS_AUT);
}
void auscultation_widget::on_HS_btn()
{
    btnInit();
    ui->HS_bt->setStyleSheet(QString("image:url(:/images/clicked.png)"));
    emit aut_btn_id(ID_HS_AUT);
}

void auscultation_widget::setBtnFoucse(int index)
{
    btnInit();
    switch(index)
    {
    case 0:
        ui->HS_bt->setStyleSheet(QString("image:url(:/images/clicked.png)"));
        break;
    case 1:
        ui->BS_btn->setStyleSheet(QString("image:url(:/images/clicked.png)"));
    default:
        break;
    }
}
void auscultation_widget::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
