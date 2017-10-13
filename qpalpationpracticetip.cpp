#include "qpalpationpracticetip.h"
#include "ui_qpalpationpracticetip.h"

QPalpationpracticeTip::QPalpationpracticeTip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QPalpationpracticeTip)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    m_movie=new QMovie(QCoreApplication::applicationDirPath()+QString("/Avatar/loading.gif"));
    ui->Gif_label->setMovie(m_movie);
}

QPalpationpracticeTip::~QPalpationpracticeTip()
{
    delete m_movie;
    delete ui;
}
void QPalpationpracticeTip::SetTitle(QString &Title)
{
    this->setWindowTitle(Title);
}
void QPalpationpracticeTip::m_exec()
{
    m_movie->start();
    this->exec();
}
