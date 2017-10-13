#include "myswitchbutton.h"
#include "qpainter.h"
#include "qevent.h"
#include "qtimer.h"
#include "qdebug.h"

SwitchButton::SwitchButton(QWidget *parent): QWidget(parent)
{
    checked = true;
    bgColorOff = QColor(74,171,233);
    bgColorOn = QColor(74,171,233);

    sliderColorOff = QColor(250, 250, 250);
    sliderColorOn = QColor(250,250, 250);

    textColorOff = QColor(255, 255, 255);
    textColorOn = QColor(255, 255, 255);

    textOff = QStringLiteral("");
    textOn = QStringLiteral("");
    space = 2;
    rectRadius = 5;
    step = width() / 10;
    startX = 0;
    endX = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    setFont(QFont("Microsoft Yahei", 10));
}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::mousePressEvent(QMouseEvent *)
{
    checked = !checked;
    emit checkedChanged(checked);
    //每次移动的步长为宽度的 50分之一
    step = width() / 50;
    //状态切换改变后自动计算终点坐标
    if (checked)
    {
       endX = width() - width() / 2;
    } else
    {
        endX = 0;
    }
    timer->start(10);
}

void SwitchButton::resizeEvent(QResizeEvent *)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 100;
    //尺寸大小改变后自动设置起点坐标为终点
    if (checked)
    {
      startX = width() - width() / 2;
    }
    else
    {
        startX = 0;
    }
    update();
}

void SwitchButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //绘制背景
        drawBg(&painter);
        //绘制滑块
        drawSlider(&painter);
        //绘制文字
        drawText(&painter);
}
//void SwitchButton::m_test(SwitchButton *a)
//{
//    QPainter painter(a);
//    painter.setRenderHint(QPainter::Antialiasing);
//    drawText(&painter);
//}
void SwitchButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked)
    {
        painter->setBrush(bgColorOff);
    } else
    {
        painter->setBrush(bgColorOn);
    }
        painter->drawRoundedRect(rect(), rectRadius, rectRadius);

    painter->restore();
}

void SwitchButton::drawSlider(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked) {
        painter->setBrush(sliderColorOff);
    } else {
        painter->setBrush(sliderColorOn);
    }
    int sliderWidth = width() / 2 - space * 2;
    int sliderHeight = height() - space * 2;
    QRect sliderRect(startX + space, space, sliderWidth , sliderHeight);
    painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
    painter->restore();
}

void SwitchButton::drawText(QPainter *painter)
{
    painter->save();

    if (!checked) {
        painter->setPen(textColorOff);
        painter->drawText(width() / 2, 0, width() / 2 - space, height(), Qt::AlignCenter, textOff);
    } else {
        painter->setPen(textColorOn);
        painter->drawText(0, 0, width() / 2 + space * 2, height(), Qt::AlignCenter, textOn);
    }
    painter->restore();
}

void SwitchButton::updateValue()
{
    if (checked) {
        if (startX < endX)
        {
            startX = startX + step;
        } else
        {
            startX = endX;
            timer->stop();
        }
    }
    else
    {
        if (startX > endX)
        {
            startX = startX - step;
        }
        else
        {
            startX = endX;
            timer->stop();
        }
    }
    update();
}

void SwitchButton::setChecked(bool checked)
{
    if (this->checked != checked)
    {
        this->checked = checked;
        emit checkedChanged(checked);
        step = width() / 50;
        //状态切换改变后自动计算终点坐标
        if (checked)
        {
           endX = width() - width() / 2;
        } else
        {
            endX = 0;
        }
        timer->start(5);
        update();
    }
}

void SwitchButton::setText(QString textOff, QString textOn)
{
    this->textOff = textOff;
    this->textOn = textOn;
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    drawText(&painter);
    update();

}
