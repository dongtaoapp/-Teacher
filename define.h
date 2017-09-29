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
      QString ScheduleType;//课程表类型 0:课件 1:病例 2:鉴别听诊
      QString ScheduleName;//课程表名
      QString ScheduleTime;//时间
      QString ScheduleID;//课程表ID
}ClassScheduleData;

Q_DECLARE_METATYPE(ClassScheduleData);

/*********主界面的大小**********/
#define WINDOWWIDTH 1366
#define WINDOWHEIGHT 768

/******TabWidget按钮的宽高*********/
#define BTN_TAB_WIDTH 124
#define BTN_TOP_BTN_HEIGHT 64
#define BTN_TAB_HEIGHT 38
/***********课件界面按钮ID 定义************/
#define ID_HS_CWARE 10
#define ID_ABT_CWARE 11
#define ID_ECG_CWARE 12
/************* 听诊界面按钮ID 定*********/
#define ID_HS_AUT 30
#define ID_BS_AUT 31

/** *******病例按钮ID 定义**************/
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
/**********主界面Tabbar的宏定义****************/
#define MAIN_TAB_CO 0
#define MAIN_TAB_CA 1
#define MAIN_TAB_AU 2


/*******系统设置界面ID*********/

#define EXIT 3
#define SET 4
#define TOGHER 5
#define ABOUT 6
/***读取配置文件路径*******/
#define APPPATH QCoreApplication::applicationDirPath()+QString("/data/configure.ini")

#define MYURL QString("http://192.168.1.139/")
/*****学生机状态*********/

#define ONLINE 130
#define OFFLINE 140
#define REQUEST 150

#endif // DEFINE_H
