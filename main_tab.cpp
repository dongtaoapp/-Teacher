#include "main_tab.h"
#include <qDebug>
#include <QIcon>
#include "define.h"
main_tab::main_tab(QWidget *parent):
    QTabWidget(parent)
{
   au_widget=new auscultation_widget;//������
   ca_widget=new case_widget;//������
   co_widget=new courseware_widget;//�μ���
   this->setWindowFlags(Qt::FramelessWindowHint);
   this->setTabPosition(QTabWidget::South);
   insertTabwidget();
   connect(co_widget,SIGNAL(cware_btn_id(int)),this,SIGNAL(onClickedevent(int)));
   connect(au_widget,SIGNAL(aut_btn_id(int)),this,SIGNAL(onClickedevent(int)));
   connect(ca_widget,SIGNAL(case_btn_id(int)),this,SIGNAL(onClickedevent(int)));
}

main_tab::~main_tab()
{
    au_widget->deleteLater();
    ca_widget->deleteLater();
    co_widget->deleteLater();
}
void main_tab::insertTabwidget()
{
    this->insertTab(MAIN_TAB_CO,co_widget,QStringLiteral(""));
    this->insertTab(MAIN_TAB_CA,ca_widget,QStringLiteral(""));
    this->insertTab(MAIN_TAB_AU,au_widget,QStringLiteral(""));
}

void main_tab::setTypeFoucse(SetFoucseType type, int index)
{

    switch(type)
    {
    case CouswareFoucse:
        this->setCurrentIndex(MAIN_TAB_CO);
        co_widget->setBtnFoucse(index);
        break;
    case CaseFoucse:
        this->setCurrentIndex(MAIN_TAB_CA);
        ca_widget->setBtnFouse(index);
        break;
    case DiffFoucse:
        this->setCurrentIndex(MAIN_TAB_AU);
        au_widget->setBtnFoucse(index);
        break;
     default:
        break;

    }
}
