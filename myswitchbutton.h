#ifndef MYSWITCHBUTTON_H
#define MYSWITCHBUTTON_H

#include <QWidget>

class QTimer;

class SwitchButton: public QWidget
{
    Q_OBJECT
public:
    SwitchButton(QWidget *parent = 0);
    ~SwitchButton();
protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawText(QPainter *painter);
    void drawImage(QPainter *painter);

private:
    bool checked;               //是否选中
    QColor bgColorOff;          //关闭时背景颜色
    QColor bgColorOn;           //打开时背景颜色

    QColor sliderColorOff;      //关闭时滑块颜色
    QColor sliderColorOn;       //打开时滑块颜色

    QColor textColorOff;        //关闭时文本颜色
    QColor textColorOn;         //打开时文本颜色

    QString textOff;            //关闭时显示的文字
    QString textOn;             //打开时显示的文字
    int space;                  //滑块离背景间隔
    int rectRadius;             //圆角角度
    int step;                   //每次移动的步长
    int startX;                 //滑块开始X轴坐标
    int endX;                   //滑块结束X轴坐标
    QTimer *timer;              //定时器绘制

private slots:
    void updateValue();

public :
    //设置是否选中
    void setChecked(bool checked);
public slots:
//    //设置是否选中
//    void setChecked(bool checked);
    //设置文本
    void setText(QString textOff, QString textOn);

    QString TextOFF(){return textOff;}
    QString TextON(){return textOn;}
signals:
    void checkedChanged(bool checked);
};

#endif // MYSWITCHBUTTON_H
