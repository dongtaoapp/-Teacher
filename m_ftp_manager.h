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
    void setHostport(QString &host,int port=21);//  ���õ�ַ�Ͷ˿�
    void setUserInfo(QString &username,QString &userpassword);// ���õ�¼ FTP ���������û���������
    void GetWebIp();
public slots:
  //--------------�ϴ��ļ�
  void uploadfile(const QString path,const QString filename);//�ϴ��ļ� ��һ������Ϊftp�������ļ���ַ �ڶ�����������Ҫ�ϴ��ı��ص��ļ�·��
  void on_Uploadfinsh();
  //--------------��½�ӿ�
  void Login(QString Username, QString password);
  void LoginFinsh();

  //------------�����ļ�
  void downloadfile( QString &path,const QString filename);//�����ļ� ��һ������Ϊftp�������ļ���ַ �ڶ������������ص����ص��ļ�·��
  void on_downloadfinsh();
  void write_file(QByteArray &m_download_byte);//д�ļ�

  //--------------��ȡ�Զ���μ�
  void GetCustomCourse();
  void GetCustomCourseFinsh();


  //-----------------��ü�������������Ϣ
  void GetDiffSound();
  void GetDiffSoundFinsh();
//------------------���������ײ�
  void GetDiffSoundCombo(QString &ID);
  void GetDiffSoundComboFinsh();


  //---------------------�������ﵥ����Ϣ
  void GetDiffSoundFile(QString &ID);//��ȡ��������������Ϣ
  void GetDiffSoundFileFinsh();
signals:
    void m_finsh(QByteArray &m_download_byte);//�Լ���reply finsh�ź�
    void down_write_finsh();//��������ź�
    void loginstate(m_ftp_manager::LOGINSTATE,QString);
    void CustomCourseData(QByteArray &Data);//�Զ���μ���Ϣ
    void DiffSoundData(QByteArray &data);//ȫ������������Ϣ
    void DiffSoundFileData(QByteArray &data);//��������������Ϣ
    void DiffSoundComboData(QByteArray &data);//���������ײ�
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
