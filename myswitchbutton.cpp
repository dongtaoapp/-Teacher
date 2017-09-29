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
    //ÿ���ƶ��Ĳ���Ϊ��ȵ� 50��֮һ
    step = width() / 50;
    //״̬�л��ı���Զ������յ�����
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
    //ÿ���ƶ��Ĳ���Ϊ��ȵ� 50��֮һ
    step = width() / 100;
    //�ߴ��С�ı���Զ������������Ϊ�յ�
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
    //����׼������,���÷����
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //���Ʊ���
        drawBg(&painter);
        //���ƻ���
        drawSlider(&painter);
        //��������
        drawText(&painter);
}

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
        if (startX < endX) {
            startX = startX + step;
        } else {
            startX = endX;
            timer->stop();
        }
    } else
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
   // if (this->checked != checked)
 //   {
        this->checked = checked;

         qDebug()<<__FUNCTION__<<checked;
        emit checkedChanged(checked);
        update();
  //  }
}

void SwitchButton::setText(QString textOff, QString textOn)
{
    this->textOff = textOff;
    this->textOn = textOn;
    update();
}
