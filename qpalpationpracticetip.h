#ifndef QPALPATIONPRACTICETIP_H
#define QPALPATIONPRACTICETIP_H

#include <QDialog>
#include <QMovie>
namespace Ui {
class QPalpationpracticeTip;
}

class QPalpationpracticeTip : public QDialog
{
    Q_OBJECT

public:
    explicit QPalpationpracticeTip(QWidget *parent = 0);
    ~QPalpationpracticeTip();
    void SetTitle(QString &Title);
    void m_exec();
private:
    Ui::QPalpationpracticeTip *ui;
    QMovie *m_movie;
};

#endif // QPALPATIONPRACTICETIP_H
