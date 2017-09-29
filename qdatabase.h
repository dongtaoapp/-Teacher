#ifndef QDATABASE_H
#define QDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QString>
typedef struct loginInfo{
    QString name;
    QString pw;
    bool Rbpw;
    QString HeadImage;

}loginInfo;

class QDataBase : public QObject
{
    Q_OBJECT
public:
    QDataBase();
    ~QDataBase();

    QList<loginInfo> teacherInfo();


    void insertInfo(loginInfo &info);

    void updateInfo(loginInfo &info);

private:
    QSqlDatabase db;
};

#endif // QDATABASE_H
