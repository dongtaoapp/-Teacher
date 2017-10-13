#include "qtrainmainwindow.h"
#include "loginbackgroundform.h"
#include "qchosecurriculumview.h"
#include "m_ftp_manager.h"
#include "qcoursewareinfo.h"
#include <QApplication>
#include <QObject>
#include <QByteArray>
#include <QHostAddress>
#include <QThread>
#include <QMetaType>
#include <QByteArray>

void GetClassScheduleData(QList<ClassScheduleData> *schedule_list)
{



}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<m_ftp_manager::LOGINSTATE>("LOGINSTATE");
    qRegisterMetaType<QByteArray>("QByteArray &");
    qRegisterMetaType<stardardCase>("stardardCase &");
    qRegisterMetaType<diffSound>("diffSound &");
    qRegisterMetaType<QString>("QString &");
    qDebug()<<"main thread"<<QThread::currentThreadId();


    QTrainMainWindow w;

//    w.InitShow();
    w.ClassScheduleInit();

//    w.setCurriculumID(aa);

//    LoginBackgroundForm  *t=new LoginBackgroundForm;
//    t->show();

////    QChoseCurriculumView Ch;

////    Ch.addCurriculum(Data1);
////    Ch.addCurriculum(Data2);
//  //  Ch.show();

//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),&w,SLOT(doLoginsuccess(QString&,QString&)));
//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),&w,SLOT(GetDiffData()));
//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),&w,SLOT(ClassScheduleInit()));
//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),t,SLOT(deleteLater()));

//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),&w,SLOT(show()));
//    QObject::connect(&Ch,SIGNAL(CLNum(QString&)),&w,SLOT(setCurriculumID(QString&)));
//    QObject::connect(t,SIGNAL(dologinSuccess(QString&,QString&)),&w,SLOT(InitSoundControl()));
//    QObject::connect(&Ch,SIGNAL(CLNum(QString &)),&w,SLOT(show()));


    return a.exec();
}
