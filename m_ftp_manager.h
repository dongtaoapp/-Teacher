#ifndef M_FTP_MANAGER_H
#define M_FTP_MANAGER_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QThread>
#include <qobjectdefs.h>
#include <QMetaType>
#include <QMutex>
class m_ftp_manager:public QObject
{
    Q_OBJECT
public:
    enum LOGINSTATE{
        LOGINSUCCESS=0,
        LOGINFAILED=1,
        NAMEPWERROR=2,
        NONAME=3,
        UNKNOWERROR
    };
    Q_ENUM(LOGINSTATE)
    explicit  m_ftp_manager();
    ~m_ftp_manager();
    void setHostport(QString &host,int port=21);//  设置地址和端口
    void setUserInfo(QString &username,QString &userpassword);// 设置登录 FTP 服务器的用户名和密码
    void GetWebIp();
public slots:
  //--------------上传文件
  void uploadfile(const QString path,const QString filename);//上传文件 第一个参数为ftp服务器文件地址 第二个参数是需要上传的本地的文件路径
  void on_Uploadfinsh();
  //--------------登陆接口
  void Login(QString Username, QString password);
  void LoginFinsh();

  //------------下载文件
  void downloadfile( QString &path,const QString filename);//下载文件 第一个参数为ftp服务器文件地址 第二个参数是下载到本地的文件路径
  void on_downloadfinsh();
  void write_file(QByteArray &m_download_byte);//写文件

  //--------------获取自定义课件
  void GetCustomCourse();
  void GetCustomCourseFinsh();


  //-----------------获得鉴别听诊所有信息
  void GetDiffSound();
  void GetDiffSoundFinsh();
//------------------鉴别听诊套餐
  void GetDiffSoundCombo(QString &ID);
  void GetDiffSoundComboFinsh();
  //---------------------鉴别听诊单个信息
  void GetDiffSoundFile(QString &ID);//获取鉴别听诊声音信息
  void GetDiffSoundFileFinsh();
signals:
    void m_finsh(QByteArray &m_download_byte);//自己的reply finsh信号
    void down_write_finsh();//整个完成信号
    void loginstate(m_ftp_manager::LOGINSTATE,QString);
    void CustomCourseData(QByteArray &Data);//自定义课件信息
    void DiffSoundData(QByteArray &data);//全部鉴别听诊信息
    void DiffSoundFileData(QByteArray &data);//鉴别听诊声音信息
    void DiffSoundComboData(QByteArray &data);//鉴别听诊套餐
private:

    QNetworkAccessManager *m_manager;
    QNetworkReply *up_reply;
    QNetworkReply *down_reply;
    QNetworkReply *post_reply;
    QNetworkReply *aaatest;
    QUrl m_url;
    QFile *m_file;
    QByteArray m_download_byte;
    QString all_filename;

    QJsonArray jarry;
    QJsonDocument jdocument;
    QJsonObject jobject;
//    QThread ftpthread;

    QMutex postMutex;

    QString m_WebIP;
};
//Q_DECLARE_METATYPE(m_ftp_manager)
#endif // M_FTP_MANAGER_H
