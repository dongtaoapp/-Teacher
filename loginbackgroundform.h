#ifndef LOGINBACKGROUNDFORM_H
#define LOGINBACKGROUNDFORM_H

#include <QWidget>
#include <loginform.h>
#include <QLabel>
#include <QPushButton>
class LoginBackgroundForm : public  QWidget
{
    Q_OBJECT
public:

    LoginBackgroundForm(QWidget *parent=Q_NULLPTR);
    ~LoginBackgroundForm();
    void windowInit();
    void loadqss();
protected:
     void paintEvent(QPaintEvent *event);
     void closeEvent(QCloseEvent *event);
public slots:
     void m_delete();
signals:
     void m_close();
     void dologinSuccess(QString& name,QString& avatar);
private:
    LoginForm *loginform;
    QLabel *backgroundLabel;
    QLabel *m_title_label;
    QPushButton *m_close_btn;
};

#endif // LOGINBACKGROUNDFORM_H
