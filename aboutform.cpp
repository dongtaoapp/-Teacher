#include "aboutform.h"
#include "ui_aboutform.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <qDebug>
AboutForm::AboutForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutForm)
{
    ui->setupUi(this);
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    this->setWindowTitle(QStringLiteral("�������"));
}

AboutForm::~AboutForm()
{
    delete ui;
}
