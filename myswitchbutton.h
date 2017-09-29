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
    bool checked;               //�Ƿ�ѡ��
    QColor bgColorOff;          //�ر�ʱ������ɫ
    QColor bgColorOn;           //��ʱ������ɫ

    QColor sliderColorOff;      //�ر�ʱ������ɫ
    QColor sliderColorOn;       //��ʱ������ɫ

    QColor textColorOff;        //�ر�ʱ�ı���ɫ
    QColor textColorOn;         //��ʱ�ı���ɫ

    QString textOff;            //�ر�ʱ��ʾ������
    QString textOn;             //��ʱ��ʾ������
    int space;                  //�����뱳�����
    int rectRadius;             //Բ�ǽǶ�
    int step;                   //ÿ���ƶ��Ĳ���
    int startX;                 //���鿪ʼX������
    int endX;                   //�������X������
    QTimer *timer;              //��ʱ������

private slots:
    void updateValue();

public :
    //�����Ƿ�ѡ��
    void setChecked(bool checked);
public slots:
//    //�����Ƿ�ѡ��
//    void setChecked(bool checked);
    //�����ı�
    void setText(QString textOff, QString textOn);

    QString TextOFF(){return textOff;}
    QString TextON(){return textOn;}
signals:
    void checkedChanged(bool checked);
};

#endif // MYSWITCHBUTTON_H
