#include "qdatabase.h"
#include "define.h"
#include <qDebug>
#include <QSqlError>
#include <QCoreApplication>
QDataBase::QDataBase()
{
   db=QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
                       .arg(QCoreApplication::applicationDirPath()+QString("/data/LoginInfo.mdb")));

 //  db.setDatabaseName(QCoreApplication::applicationDirPath()+QString("/data/LoginInfo.mdb"));
   if( db.open())
   {
      qDebug()<<"database open";
   }
}

QDataBase::~QDataBase()
{
    qDebug()<<__FUNCTION__;
    db.close();
}

QList<loginInfo> QDataBase::teacherInfo()
{
    loginInfo info;
    QList<loginInfo> list;
    QSqlQuery query(db);
       query.prepare("select * from Info");
       if(!query.exec())
       {
             qDebug()<<__FUNCTION__<<query.lastError();
             return list;
       }
       else
       {
            while(query.next())
            {
              info.name=query.value("LoginName").toString();
              info.pw=query.value("LoginPw").toString();
              info.Rbpw=query.value("Rbpw").toBool();
              info.HeadImage=query.value("HeadImage").toString();
              list.append(info);
            }
       }
       return list;
}
void QDataBase::insertInfo(loginInfo &info)
{
    QSqlQuery query(db);
    if(!query.exec(QString("insert into Info(LoginName,LoginPw,Rbpw,HeadImage) values('%1','%2',%3,'%4')")
                   .arg(info.name).arg(info.pw).arg(info.Rbpw).arg(info.HeadImage)))
    {
         qDebug()<<__FUNCTION__<<query.lastError();
    }
    else
    {
         qDebug()<<__FUNCTION__<<"inserted!";
    }
}
void QDataBase::updateInfo(loginInfo &info)
{
    QSqlQuery query(db);
    if(!query.exec(QString("update Info set LoginPw='%1',Rbpw=%2,HeadImage='%3' where LoginName='%4'")
                   .arg(info.pw).arg(info.Rbpw).arg(info.HeadImage).arg(info.name)))
    {
         qDebug()<<__FUNCTION__<<query.lastError();
    }
    else
    {
         qDebug()<<__FUNCTION__<<"updatede!";
    }
}
