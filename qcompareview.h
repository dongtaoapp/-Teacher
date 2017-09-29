#ifndef QCOMPAREVIEW_H
#define QCOMPAREVIEW_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPalette>
#include <QTimer>
#include <QDebug>
#include <QTimeLine>
#include "globalcommon.h"
namespace Ui {
class QCompareView;
}

class QCompareView : public QDialog
{
    Q_OBJECT

public:
    explicit QCompareView(QWidget *parent = 0);
    ~QCompareView();
    int SoundNum(){return m_soundNum;}
public slots:
    void addComopareMsg(diffSound &data);//添加对比音源
    void onUiCompareBtn();//开始对比信息


    void onUideleteBtnFirst();
    void onUideleteBtnSecond();
    void onUiemityBtn();
    void widgetinit();

    void setEmpityBtnWork(bool work);
signals:
    void CompareBntCilcked(diffSound&,diffSound&);

    void deleteDiffSound1(diffSound &);
    void deleteDiffSound2(diffSound &);
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::QCompareView *ui;
    int m_soundNum;

    diffSound labelData1;
    diffSound labelData2;
};

#endif // QCOMPAREVIEW_H
