#ifndef DEFINE_H
#define DEFINE_H

//LoginName varchar,LoginPw varchar,Rbpw bool,HeadImage varchar
#include<QVariant>
#include <QString>
#include <QCoreApplication>
struct videoPack{
char    data[1024];
int     lens;
};
typedef struct ClientIdIp{
    QString DeskId;
    QString DeskIp;

}ClientIdIp;

typedef struct Tab_Btn_Data{
    int FatherID;
    int sonID;
}Tab_Btn_Data;

Q_DECLARE_METATYPE(Tab_Btn_Data);

typedef struct ClassScheduleData{
      QString ScheduleType;//�γ̱����� 0:�μ� 1:���� 2:��������
      QString ScheduleName;//�γ̱���
      QString ScheduleTime;//ʱ��
      QString ScheduleID;//�γ̱�ID
}ClassScheduleData;

Q_DECLARE_METATYPE(ClassScheduleData);

/*********������Ĵ�С**********/
#define WINDOWWIDTH 1366
#define WINDOWHEIGHT 768

/******TabWidget��ť�Ŀ��*********/
#define BTN_TAB_WIDTH 124
#define BTN_TOP_BTN_HEIGHT 64
#define BTN_TAB_HEIGHT 38
/***********�μ����水ťID ����************/
#define ID_HS_CWARE 10
#define ID_ABT_CWARE 11
#define ID_ECG_CWARE 12
/************* ������水ťID ��*********/
#define ID_HS_AUT 30
#define ID_BS_AUT 31

/** *******������ťID ����**************/
#define ID_HS_CASE 20
#define ID_HS_ALL_CASE 200
#define ID_HS_ADULT_CASE 201
#define ID_HS_CHILD_CASE 202
#define ID_HS_OLD_CASE 203

#define ID_ABS_CASE 21
#define ID_ABS_ALL_CASE 210
#define ID_ABS_ADULT_CASE 211
#define ID_ABS_CHILD_CASE 212
#define ID_ABS_OLD_CASE 213

#define ID_BBGS_CASE 22
#define ID_BBGS_ALL_CASE 220
#define ID_BBGS_ADULT_CASE 221
#define ID_BBGS_CHILD_CASE 222
#define ID_BBGS_OLD_CASE 223


#define FLASHPLAY "<invoke name=\"StartFlashFunc\"><arguments></arguments></invoke>"
#define FLASHPAUSE "<invoke name=\"PauseFlashFunc\"><arguments></arguments></invoke>"
/**********������Tabbar�ĺ궨��****************/
#define MAIN_TAB_CO 0
#define MAIN_TAB_CA 1
#define MAIN_TAB_AU 2


/*******ϵͳ���ý���ID*********/

#define EXIT 3
#define SET 4
#define TOGHER 5
#define ABOUT 6
/***��ȡ�����ļ�·��*******/
#define APPPATH QCoreApplication::applicationDirPath()+QString("/data/configure.ini")

#define MYURL QString("http://192.168.1.139/")
/*****ѧ����״̬*********/

#define ONLINE 130
#define OFFLINE 140
#define REQUEST 150

#endif // DEFINE_H
