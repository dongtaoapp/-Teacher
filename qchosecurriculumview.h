#ifndef QCHOSECURRICULUMVIEW_H
#define QCHOSECURRICULUMVIEW_H
#define  CurriculumItemHeight 60
#define  CurriculumItemWidth 564
#include <QWidget>
#include <QLabel>
#include <QDialog>
#include <QRadioButton>
#include <QScrollArea>
#include <QMap>
#include <QList>
#include <QString>
#include <QPushButton>
#include <QMouseEvent>
#include "define.h"
//typedef struct CurriculumInfo{

//   QString Type;
//   QString id;
//   QString name;
//   QString time;


//}CurriculumInfo;


class  CurriculumItem :public QWidget
{
    Q_OBJECT
public:
     CurriculumItem (QWidget *parnet=Q_NULLPTR);
     ~CurriculumItem();
     void itemSetInit();//��ʼ���ؼ�λ��
     ClassScheduleData ItemData(){return m_data;}
     void setCurriculumMsg(ClassScheduleData Data);
signals:
     void m_clicked(bool);
protected:
      void paintEvent(QPaintEvent *event);
      void mousePressEvent(QMouseEvent *event);
private:
      ClassScheduleData m_data;
      QLabel *CurriculumName;
      QLabel *CurriculumTime;
      bool clicked;
};


class QChoseCurriculumView :public QDialog
{
      Q_OBJECT
public:
    QChoseCurriculumView(QWidget *parent=Q_NULLPTR);
    ~QChoseCurriculumView();
    void windowInit();//�ؼ���ʼ��
    void setPosition();//�ؼ�λ������
    void loadqss();
//    int setCurriculumNum(){return CurriculumMsg_list.size();}//���ؿγ�����
    void addCurriculum(ClassScheduleData &data);

    void setClassScheduleChecked(QString &ID);//��ѡ�γ�


private slots:
    void onOkbnt();
    void onCancelBtn();
signals:
    void CLNum(ClassScheduleData &num);//����ѡ��Ŀγ�id �ź� ���ȷ��ʱ����

    void m_close();

protected:
     void mousePressEvent (QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent * event);
     void paintEvent(QPaintEvent *event);
     void closeEvent(QCloseEvent *);
private:
   int xOffset,yOffset;
    QLabel *top_label;
    QLabel *title_label;
    QPushButton *close_btn;
    QPushButton *ok_btn;
    QPushButton *cancel_btn;

    QRadioButton *chosedBtn;
    QWidget *CurriculumWidget;
    QScrollArea *CurriculumScrollArea;

//    QList<ClassScheduleData> CurriculumMsg_list;

    ClassScheduleData m_data;
    QMap<QRadioButton *,CurriculumItem *> item_map;

    int num;
};

#endif // QCHOSECURRICULUMVIEW_H
