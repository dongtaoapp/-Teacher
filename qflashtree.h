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
      bool Casecolum0Clicked;//�жϲ����Ƿ����ȵ��Cloum0��
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
     CORDIOPHONY,//�������ﲡ��
     LUNGAUSCULTATION,//�β����ﲡ��
     Borborygmus,//������������
    };
    enum DiffType{
        HEARTDIFF,//��������
        BREATHDIFF,//����������
    };
    enum CourseWareType{
        HeartLungCourse,//�ķομ�
        ABTCourse,//��������μ�
        ECGCourse,//�ĵ�ͼ�μ�

    };
    qFlashTreeBase(QWidget *parent=0);
    ~qFlashTreeBase(){;}
    void treeInit();
    void CouseWareStyleSheet();
    void setCaseTree(CaseType type);//��������ͼΪ��������ͼ
    void m_ShowHiden(int type);

    void setDiffTree(DiffType type);//��������ͼΪ������������ͼ

    void setCouseWare(CourseWareType type);
    void constructionCouseWareTree(QMapIterator<QString, QCoursewareInfo> &map);
    void GetSonNum();
    int GetAllSonNum(QTreeWidgetItem *item);

signals:
    void FlahsItemData(QCoursewareInfo &info);//����flash Item��Ϣ
    void webItemData(userCourseware &);//�Զ��� �μ�Item ��Ϣ
    void CaseItemData(stardardCase &);//���� Item ��Ϣ
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
    //---------------------------�μ���ؽӿ�
    void SetCustomcoursewareTree(CourseWareType type);//�Զ���μ�����ͼ
    void GetCustomCourseWareData(QByteArray &Data);
    void GetCustomCouseDataFinsh();
    void StartGetLocalCouseWare();
    void GetLocalCouseWareABT();
    void GetLocalCouseWareECG();

    //-----------------------������ؽӿ�
    void GetCaseData();
    void addCaseChildItem(QString &Type,stardardCase &Case);
    QTreeWidgetItem *GetCaseItem(int index);
    QString CaseIdMsg(){return m_CaseIDMsg;}
    //--------------����������ؽӿ�
    void GetDiffSoundData(QByteArray &Data);
    void DiffSoundItemClicked(QString &ID);
    void addDiffSoundChild(QTreeWidgetItem *fatherItem ,const diffSound &Data);
public:
//     QMap<QString,QTreeWidgetItem*> Item_map;//�洢���ڵ�

    //------------------�μ���ر���
    QMap<QString,QCoursewareInfo> CourseWareHL_map; //�ķ�
    QMap<QString,QCoursewareInfo> CourseWareABT_map; //����
    QMap<QString,QCoursewareInfo> CourseWareECG_map; //�ĵ�ͼ

    QList<userCourseware*> lstUserCourseware;//�Զ���μ�List
    QParseCourseWareFileOp    *ReadJsonWorkhl;
    QParseCourseWareFileOp    *ReadJsonWorkABT;
    QParseCourseWareFileOp    *ReadJsonWorkECG;

    //--------------������ر���

    QTreeWidgetItem *adult;
    QTreeWidgetItem *child;
    QTreeWidgetItem *old;
    QList<stardardCase> lststardardCase;//��׼����������
    QMap<QString,TreeItemWidget*> TreeItemWidget_map;//��������ͼ����Map;
    QMap<int,QTreeWidgetItem*> CaseTreeItem_map;


    //---------------�����������
    QList<diffSound> lstDiffSound;//����������Ϣ����
    QMap<QString,diffSound> DiffSoundTreewidget_map;//Item Data Map
    QMap<QString,TreeItemWidget *> Treewidget_map;//Item widget Map
    QMap<QString,QString> heartDiffFatherItem_Map;//���� ���ڵ� Map
    QMap<QString,QString> breathDiffFatherItem_Map;//������ ���ڵ� Map
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
