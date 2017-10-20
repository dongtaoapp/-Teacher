#ifndef QFLASHTREE_H
#define QFLASHTREE_H

#include <QObject>
#include <QTreeWidget>
#include <QMap>
#include <QString>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QWidget>
#include "qparsecoursewarefileop.h"
#include "m_ftp_manager.h"
#include "globalcommon.h"
#include <QWidget>
#include <QLabel>
class TreeItemWidget : public QWidget

{
    Q_OBJECT
public :
    enum TreeItemWidgetType{
            CaseWidget,
            DiffSoundWidget
    };
    TreeItemWidget(QWidget *parent=Q_NULLPTR,TreeItemWidgetType Type=CaseWidget);
    ~TreeItemWidget(){;}

     void setTreeItemWidgetType(TreeItemWidgetType type);
     void changStyle(QString &str);

     void changBtnStyle(QString &str);

     void setBtnData(const QString &data);
public:
      bool Casecolum0Clicked;//判断病例是否是先点击Cloum0；
public slots:
      void btnClicked();

      void DiffSoundFull(bool aa);

      void restoreBtn();
signals:
      void btnClickedtimes(QString &ID);
public:
    QLabel *m_label;
    QPushButton *btn;

    QString ID;
    int canadd;

};


class qFlashTreeBase : public QTreeWidget
{
    Q_OBJECT
public:
    enum CaseType{
     CORDIOPHONY,//心音听诊病例
     LUNGAUSCULTATION,//肺部听诊病例
     Borborygmus,//肠鸣音听病例
    };
    enum DiffType{
        HEARTDIFF,//心音鉴别
        BREATHDIFF,//呼吸音鉴别
    };
    enum CourseWareType{
        HeartLungCourse,//心肺课件
        ABTCourse,//腹部触诊课件
        ECGCourse,//心电图课件

    };
    qFlashTreeBase(QWidget *parent=0);
    ~qFlashTreeBase(){;}
    void treeInit();
    void CouseWareStyleSheet();
    void setCaseTree(CaseType type);//设置树行图为病例树形图
    void m_ShowHiden(int type);

    void setDiffTree(DiffType type);//设置树形图为鉴别听诊树形图

    void setCouseWare(CourseWareType type);
    void constructionCouseWareTree(QMapIterator<QString, QCoursewareInfo> &map);
    void GetSonNum();
    int GetAllSonNum(QTreeWidgetItem *item);

signals:
    void FlahsItemData(QCoursewareInfo &info);//本地flash Item信息
    void webItemData(userCourseware &);//自定义 课件Item 信息
    void CaseItemData(stardardCase &);//病例 Item 信息
//    void AllTeachCaseItem(QString &data);
    void DiffSound(diffSound &);
    void TreeItemWidgetID(QString &);

    void readJsonFileFinsh();
    void DiffSoundFull(bool);
    void m_test();
public slots:
    void restoreTreeItemWidget(diffSound &Data);
    void OnTreeCtrlScroll(int n);
    void doItemClicked(QTreeWidgetItem* item,int colum);
    //---------------------------课件相关接口
    void SetCustomcoursewareTree(CourseWareType type);//自定义课件树形图
    void GetCustomCourseWareData(QByteArray &Data);
    void GetCustomCouseDataFinsh();
    void StartGetLocalCouseWare();
    void GetLocalCouseWareABT();
    void GetLocalCouseWareECG();

    //-----------------------病例相关接口
    void GetCaseData();
    void addCaseChildItem(QString &Type,stardardCase &Case);
    QTreeWidgetItem *GetCaseItem(int index);
    QString CaseIdMsg(){return m_CaseIDMsg;}
    //--------------鉴别听诊相关接口
    void GetDiffSoundData(QByteArray &Data);
    void DiffSoundItemClicked(QString &ID);
    void addDiffSoundChild(QTreeWidgetItem *fatherItem ,const diffSound &Data);
public:
//     QMap<QString,QTreeWidgetItem*> Item_map;//存储父节点

    //------------------课件相关变量
    QMap<QString,QCoursewareInfo> CourseWareHL_map; //心肺
    QMap<QString,QCoursewareInfo> CourseWareABT_map; //腹部
    QMap<QString,QCoursewareInfo> CourseWareECG_map; //心电图

    QList<userCourseware*> lstUserCourseware;//自定义课件List
    QParseCourseWareFileOp    *ReadJsonWorkhl;
    QParseCourseWareFileOp    *ReadJsonWorkABT;
    QParseCourseWareFileOp    *ReadJsonWorkECG;

    //--------------病例相关变量

    QTreeWidgetItem *adult;
    QTreeWidgetItem *child;
    QTreeWidgetItem *old;
    QList<stardardCase> lststardardCase;//标准化病例链表
    QMap<QString,TreeItemWidget*> TreeItemWidget_map;//病例树形图子项Map;
    QMap<int,QTreeWidgetItem*> CaseTreeItem_map;


    //---------------鉴别听诊变量
    QList<diffSound> lstDiffSound;//鉴别听诊信息链表
    QMap<QString,diffSound> DiffSoundTreewidget_map;//Item Data Map
    QMap<QString,TreeItemWidget *> Treewidget_map;//Item widget Map
    QMap<QString,QString> heartDiffFatherItem_Map;//心音 父节点 Map
    QMap<QString,QString> breathDiffFatherItem_Map;//呼吸音 父节点 Map
public:
    int m_nMaxTreeCoursewareLen;
    QString jsonPath;
    CourseWareType m_Coursetype;
    QByteArray m_CustomCourseData;

    int items;


    QString m_CaseIDMsg;

    QString m_default;
    QTreeWidgetItem *DefaultPtr=Q_NULLPTR;

};
#endif // QFLASHTREE_H
