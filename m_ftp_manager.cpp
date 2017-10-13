#include "m_ftp_manager.h"
#include "define.h"
#include <qDebug>
#include <QNetworkRequest>
#include <QFileInfo>
#include <QSettings>
m_ftp_manager::m_ftp_manager()
{
    m_url.setScheme(QString("ftp"));
    m_manager=new QNetworkAccessManager(this);
    up_reply=Q_NULLPTR;
    down_reply=Q_NULLPTR;
    m_file=new QFile;
    GetWebIp();
    m_download_byte.clear();
}

m_ftp_manager::~m_ftp_manager()
{
    m_manager->deleteLater();
    delete m_file;
}
void m_ftp_manager::setUserInfo(QString &username, QString &userpassword)
{
    m_url.setUserName(username);
    m_url.setPassword(userpassword);
}
void m_ftp_manager::setHostport(QString &host, int port)
{
    m_url.setHost(host);
    m_url.setPort(port);
}
void m_ftp_manager::GetWebIp()
{
    QSettings *readWebIP= new QSettings(APPPATH,QSettings::IniFormat);
    m_WebIP=readWebIP->value("System_Param/WebIP").toString();
    delete readWebIP;
}
//---------------上传接口
void m_ftp_manager::uploadfile( QString path,  QString filename)
{
   QFile file(filename);
   if(!file.open(QIODevice::ReadOnly))
   {
           qDebug()<<file.errorString();
           return;
   }
   QByteArray data = file.readAll();
   m_url.setPath(path);
   up_reply = m_manager->put(QNetworkRequest(m_url), data);
   connect(up_reply,SIGNAL(finished()),this,SLOT(on_Uploadfinsh()));
}
void m_ftp_manager::on_Uploadfinsh()
{
    up_reply->deleteLater();
    up_reply=Q_NULLPTR;
}

//-----------------下载接口
void m_ftp_manager::downloadfile(QString &path,const QString filename)
{
   all_filename=filename;
   m_url.setPath(path);
   down_reply = m_manager->get(QNetworkRequest(m_url));
   connect(down_reply,SIGNAL(finished()),this,SLOT(on_downloadfinsh()));
}
void m_ftp_manager::on_downloadfinsh()
{
    m_download_byte=down_reply->readAll();
    write_file(m_download_byte);
    m_download_byte.clear();
    down_reply->deleteLater();
    down_reply=Q_NULLPTR;

}
void m_ftp_manager::write_file(QByteArray &m_download_byte)
{
    switch (down_reply->error())
    {
      case QNetworkReply::NoError :
      {
        m_file->setFileName(all_filename);
         if( !m_file->open(QIODevice::WriteOnly))
          {
              qDebug()<<m_file->errorString();
          }
         if(m_file->write(m_download_byte)==m_download_byte.size())
         {
             qDebug()<<__FUNCTION__<<"Write file success";
             emit down_write_finsh();
         }
       }
            break;
        default:
            break;
       }
       m_file->close();
       all_filename.clear();
}

//-------------登陆接口
void m_ftp_manager::Login(QString Username,QString password)
{
       QString baseUrl=QString("http://%1/index.php?bodyapi-app-bodycheck-loginCheck").arg(m_WebIP);
       QUrl url(baseUrl);
       QString cmd=QString("user_username=%1&user_password=%2&user_type=1").arg(Username).arg(password);
       QNetworkRequest request;
       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
       request.setUrl(url);
       postMutex.lock();
       post_reply= m_manager->post(request,cmd.toLocal8Bit());
       connect(post_reply,SIGNAL(finished()),this,SLOT(LoginFinsh()));
}
void m_ftp_manager::LoginFinsh()
{
  QByteArray postbyte=post_reply->readAll();
  post_reply->deleteLater();
  post_reply=Q_NULLPTR;
  postMutex.unlock();

  QJsonParseError simp_json_error;
  LOGINSTATE m_state;
  QJsonDocument jdocument =QJsonDocument::fromJson(postbyte,&simp_json_error);
  if(simp_json_error.error==QJsonParseError::NoError)
  {      QJsonObject object=jdocument.object();
      if(object.isEmpty())
     {
          return;
      }
       QString state=object.value("state").toString();
       QString reason=object.value("reason").toString();
       QString user_pic=object.value("user_pic").toString();
       if(state=="1")
       {
           m_state=LOGINSUCCESS;
       }
       else if(state=="0")
       {
           if(reason=="0")
           {
              m_state=NAMEPWERROR;
           }
           else if(reason=="1")
           {
              m_state=NONAME;
           }
       }
    emit loginstate(m_state,user_pic);
    return;
  }
  else
  {
      qDebug()<<__FUNCTION__<<simp_json_error.errorString();
  }
  emit loginstate(UNKNOWERROR,QString(""));
}

//--------------获得自定义课件接口
void m_ftp_manager::GetCustomCourse()
{
    QString baseUrl=QString("http://%1/index.php?bodyapi-app-bodycheck-getAllCustomCourse").arg(m_WebIP);
    QUrl url(baseUrl);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setUrl(url);
    postMutex.lock();
    post_reply=m_manager->post(request,QByteArray(""));
    connect(post_reply,SIGNAL(finished()),this,SLOT(GetCustomCourseFinsh()));

}
void m_ftp_manager::GetCustomCourseFinsh()
{
    QByteArray data=post_reply->readAll();
    post_reply->deleteLater();
    post_reply=Q_NULLPTR;
    postMutex.unlock();
    if(data.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"CustomCourse Data is empty"<<"++++++++++++++++++++++";
      //  return ;
    }
//    QByteArray byte="gggg";
    emit CustomCourseData(data);
}

//--------------获得全部鉴别听诊信息
void m_ftp_manager::GetDiffSound()
{
    QString baseUrl=QString("http://%1/index.php?bodyapi-app-bodycheck-getAllDiscern").arg(m_WebIP);
    QUrl url(baseUrl);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setUrl(url);
    postMutex.lock();
    post_reply=m_manager->post(request,QByteArray(""));
    connect(post_reply,SIGNAL(finished()),this,SLOT(GetDiffSoundFinsh()));
}
void m_ftp_manager::GetDiffSoundFinsh()
{
    QByteArray data=post_reply->readAll();
    post_reply->deleteLater();
    post_reply=Q_NULLPTR;
    postMutex.unlock();
    if(data.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"no DiffSound ";
        return;
    }
    emit DiffSoundData(data);
}

//-------------获得鉴别听诊声音信息
void m_ftp_manager::GetDiffSoundFile(QString &ID)
{
    QString baseUrl=QString("http://%1/index.php?bodyapi-app-bodycheck-getSoundByCaseId").arg(m_WebIP);
    QUrl url(baseUrl);
    QString cmd=QString("case_id=%1").arg(ID);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setUrl(url);
    postMutex.lock();
    post_reply=m_manager->post(request,cmd.toLocal8Bit());
    connect(post_reply,SIGNAL(finished()),this,SLOT(GetDiffSoundFileFinsh()));
}
void m_ftp_manager::GetDiffSoundFileFinsh()
{
    QByteArray data=post_reply->readAll();
    post_reply->deleteLater();
    post_reply=Q_NULLPTR;
    postMutex.unlock();
    if(data.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"DiffSoundFile is emity";
        return;
    }
    emit DiffSoundFileData(data);
}

void m_ftp_manager::GetDiffSoundCombo(QString &ID)
{
    QString baseUrl=QString("http://%1/index.php?bodyapi-app-bodycheck-getDiscernPackage").arg(m_WebIP);
    QUrl url(baseUrl);
    QString cmd=QString("package_id=%1").arg(ID);
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setUrl(url);
    postMutex.lock();
    post_reply=m_manager->post(request,cmd.toLocal8Bit());
    connect(post_reply,SIGNAL(finished()),this,SLOT(GetDiffSoundComboFinshs()));
}
void m_ftp_manager::GetDiffSoundComboFinsh()
{
    QByteArray data=post_reply->readAll();
    post_reply->deleteLater();
    post_reply=Q_NULLPTR;
    postMutex.unlock();
    if(data.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"GetDiffSoundCombo Data is emity";
        return;
    }
    emit DiffSoundComboData(data);
}
