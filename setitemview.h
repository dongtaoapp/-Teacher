#ifndef SETITEMVIEW_H
#define SETITEMVIEW_H

#include <QDialog>
#include <QString>
#include <QSettings>
namespace Ui {
class SetItemView;
}

class SetItemView : public QDialog
{
    Q_OBJECT

public:
    explicit SetItemView(QWidget *parent = 0);
    ~SetItemView();
    void ReadInit();
    void Init();
    void btnInit();
public slots:
    void onBtn1();
    void onBtn2();
    void onBtn3();
    void onOkbtn();
    void oncancelBtn();
    void reload();
signals:
    void changPag(int pag);
    void reloadProcess();

    void pattern(QString );
private:
    Ui::SetItemView *ui;
    QSettings *configInit;

    int pag1_radiobtn,pag2_radiobtn,deskNumber,reloadTime;
    QString webIP;




};

#endif // SETITEMVIEW_H
