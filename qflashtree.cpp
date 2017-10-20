#include "qflashtree.h"
#include "qparseinfofromweb.h"
#include <QColor>
#include <QHeaderView>
#include <qDebug>
#include <QScrollBar>
#include <QCoreApplication>
#include <QStringList>
#include <QMapIterator>
#include <QAbstractSlider>
#include <QVariant>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>
#include <QPainter>
QCoursewareInfo Default;
QString m_CaseID;
/*****************病例Item Widget**************/
TreeItemWidget::TreeItemWidget(QWidget *parent,TreeItemWidgetType Type):
    QWidget(parent)
{
      Casecolum0Clicked=false;
      setTreeItemWidgetType(Type);
      canadd=true;
}

void TreeItemWidget::setTreeItemWidgetType(TreeItemWidgetType type)
{
    if(type==CaseWidget)
    {
        m_label=new QLabel(this);
        m_label->setGeometry(12,10,14,14);
    }
    else if(type==DiffSoundWidget)
    {
        this->resize(245,35);
        btn=new QPushButton(this);
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setGeometry(180,2,48,32);
        btn->setStyleSheet(QString("QPushButton{image:url(:/images/identify.png)}"
                                   "QPushButton:hover{image:url(:/images/identify_hover.png)}"));
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(btnClicked()));
    }
}
void TreeItemWidget::changStyle(QString &str)
{
    m_label->setStyleSheet(str);
}
void TreeItemWidget::changBtnStyle(QString &str)
{
   btn->setText(str);
}
void TreeItemWidget::btnClicked()
{
    emit btnClickedtimes(ID);
    if(canadd)
    {
         btn->setStyleSheet(QString("QPushButton{image:url(:/images/HaveInsert.png)}"));
    }
}
void TreeItemWidget::restoreBtn()
{
    btn->setStyleSheet(QString("QPushButton{image:url(:/images/identify.png)}"
                               "QPushButton:hover{image:url(:/images/identify_hover.png)}"));
}
void TreeItemWidget::setBtnData(const QString &data)
{
    ID=data;
}
void TreeItemWidget::DiffSoundFull(bool aa)
{
    canadd=aa;
}


//file:///E:/student/-/release/Resource/心脏听诊/听诊基础.swf

/************课件 病例 鉴别听诊基础树形控件******************/
qFlashTreeBase::qFlashTreeBase(QWidget *parent) :
    QTreeWidget(parent)
{
    items=0;
    m_default=QStringLiteral("/心脏听诊/听诊基础");
    treeInit();
    ReadJsonWorkhl=new QParseCourseWareFileOp;
    ReadJsonWorkABT=new QParseCourseWareFileOp;
    ReadJsonWorkECG=new QParseCourseWareFileOp;
    GetCaseData();
    StartGetLocalCouseWare();
    connect(this->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(OnTreeCtrlScroll(int)));
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(doItemClicked(QTreeWidgetItem*,int)));
}

void qFlashTreeBase::treeInit()
{
    this-> setFocusPolicy(Qt::NoFocus);
    this->resize(258,636);
    this->setColumnCount(2);
    this->setAnimated(true);
    this->setCursor(Qt::PointingHandCursor);
//    this->setStyleSheet(QString("font-size:15px; font-weight:500;"));
    QStringList headers;
    headers << QStringLiteral("flashname") <<QStringLiteral("flashNum")<<QStringLiteral("3");
    this->setHeaderLabels(headers);
    this->setHeaderHidden(true);
    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_nMaxTreeCoursewareLen=this->header()->sectionSize(0)+10;
    this->header()->setSectionResizeMode(QHeaderView::Interactive);
    this->header()->resizeSection(0,220);
    this->header()->resizeSection(2,m_nMaxTreeCoursewareLen-220);
}

//-------------------病例相关接口
void qFlashTreeBase::m_ShowHiden(int type)
{
    old->setHidden(true);
    adult->setHidden(true);
    child->setHidden(true);
    if(type==0)//显示老人
    {
      old->setHidden(false);
    }
    if(type==1)//显示成人
    {
      adult->setHidden(false);
    }
    if(type==2)//显示小孩
    {
       child->setHidden(false);
    }
    if(type==4)
    {
        old->setHidden(false);
        adult->setHidden(false);
        child->setHidden(false);
    }
}
void qFlashTreeBase::GetCaseData()
{
    QParseInfoFromWeb getCase;
    QByteArray CaseByte;
    QFile file(QCoreApplication::applicationDirPath()+QString("/json/Case.json"));
    if(file.open(QIODevice::ReadOnly))
    {
        CaseByte=file.readAll();
    }
    getCase.ParseStardardCaseInfo(CaseByte,&lststardardCase);
}
void qFlashTreeBase::setCaseTree(CaseType type)
{
    this->clear();
    this->setIndentation(15);
    this->setColumnWidth(1,46);
    this->setColumnWidth(0,212);
    TreeItemWidget_map.clear();
    if(lststardardCase.isEmpty())
    {
        qDebug()<<__FUNCTION__<<"no case Data";
        return;
    }
    this->setStyleSheet(QString("QTreeView::item:selected{background-color:#c9cacb;}"
                                "QTreeView::item:hover{background-color:#f1f2f3;}"
                                "QTreeView::item{border-style:sold;border-bottom:1px solid #e7e8e9;}"));
    adult=new QTreeWidgetItem(this);
    adult->setSizeHint(0,QSize(900,20));
    adult->setData(0,Qt::UserRole+2,QString("Case"));
    adult->setData(1,Qt::UserRole+2,QString("Case"));
    adult->setText(0,QStringLiteral("成人"));
    adult->setBackgroundColor(0,QColor(201,202,203));

    child=new QTreeWidgetItem(this);
    child->setData(0,Qt::UserRole+2,QString("Case"));
    child->setData(1,Qt::UserRole+2,QString("Case"));
    child->setSizeHint(0,QSize(9000,20));
    child->setText(0,QStringLiteral("儿童"));
    child->setBackgroundColor(0,QColor(201,202,203));

    old=new QTreeWidgetItem(this);
    old->setData(0,Qt::UserRole+2,QString("Case"));
    old->setData(1,Qt::UserRole+2,QString("Case"));
    old->setSizeHint(0,QSize(9000,20));
    old->setText(0,QStringLiteral("老人"));
    old->setBackgroundColor(0,QColor(201,202,203));
   if(type==CORDIOPHONY)
   {
     for(int i=0;i<lststardardCase.size();i++)
     {
        stardardCase Case=lststardardCase.at(i);
        if(Case.m_strType==QString("0"))
        {

            addCaseChildItem(Case.m_strHuman,Case);
        }
     }
   }
   if(type==LUNGAUSCULTATION)
   {
       for(int i=0;i<lststardardCase.size();i++)
       {
          stardardCase Case=lststardardCase.at(i);
          if(Case.m_strType==QString("1"))
          {
              addCaseChildItem(Case.m_strHuman,Case);
          }
       }
   }
   if(type==Borborygmus)
   {
       for(int i=0;i<lststardardCase.size();i++)
       {
          stardardCase Case=lststardardCase.at(i);
          if(Case.m_strType==QString("2"))
          {
               addCaseChildItem(Case.m_strHuman,Case);
          }
       }
   }
   GetSonNum();
   this->expandAll();
}
void qFlashTreeBase::addCaseChildItem(QString &Type,stardardCase &Case)
{
    QTreeWidgetItem *item;
    if(Type==QString("0"))//儿童
    {
        item=new QTreeWidgetItem(child);
    }
    else if(Type==QString("1"))//成人
    {
        item=new QTreeWidgetItem(adult);
    }
    else if(Type==QString("2"))//老人
    {
        item=new QTreeWidgetItem(old);
    }
    item->setData(0,Qt::UserRole,QVariant::fromValue(Case));
    item->setData(0,Qt::UserRole+2,QString("Case"));
    item->setData(1,Qt::UserRole+2,QString("Case"));
    item->setSizeHint(0,QSize(9000,35));
    item->setText(0,Case.m_strName);
    TreeItemWidget *ItemWidget=new TreeItemWidget(this,TreeItemWidget::CaseWidget);
    this->setItemWidget(item,1,ItemWidget);
    TreeItemWidget_map.insert(Case.m_strCaseId,ItemWidget);
    CaseTreeItem_map.insert(Case.m_strCaseId.toInt(),item);
}
QTreeWidgetItem *qFlashTreeBase::GetCaseItem(int index)
{
    return CaseTreeItem_map.find(index).value();
}
//------------------鉴别听诊相关接口
void qFlashTreeBase::GetDiffSoundData(QByteArray &Data)
{
   QParseInfoFromWeb getDiff;
   getDiff.ParseDiffSoundInfo(Data,&lstDiffSound);
   if(lstDiffSound.isEmpty())
   {
       return;
   }
   for(int i=0;i<lstDiffSound.size();i++)
   {
       diffSound data=lstDiffSound.at(i);
       if(data.m_strType==QString("0"))
       {
            heartDiffFatherItem_Map.insert(data.m_strGroupId,data.m_strGroupName);
       }
       else if(data.m_strType==QString("1"))
       {
            breathDiffFatherItem_Map.insert(data.m_strGroupId,data.m_strGroupName);
       }
   }
}
void qFlashTreeBase::setDiffTree(DiffType type)
{
    this->clear();
    this->setStyleSheet(QString("QTreeView::item:selected{color:green;}"
                                "QTreeView::item{border-style:sold;border-bottom:1px solid #bebebe;}"));;
    this->setIndentation(10);
    this->setColumnWidth(1,-100);
    this->setColumnWidth(0,258);
    items=0;
    QMap<QString,QTreeWidgetItem *> fatherItem_map;
    if(type==HEARTDIFF)
    {
        QMapIterator<QString,QString> iter(heartDiffFatherItem_Map);
        while(iter.hasNext())
        {
            iter.next();
            QTreeWidgetItem *fatherItem=new QTreeWidgetItem(this);
            fatherItem->setText(0,iter.value());
            fatherItem_map.insert(iter.key(),fatherItem);
        }
        for(int i=0;i<lstDiffSound.size();i++)
        {
             diffSound diffsound=lstDiffSound.at(i);
             if(diffsound.m_strType==QString("0"))
             {
                addDiffSoundChild(fatherItem_map.find(diffsound.m_strGroupId).value(),diffsound);
             }

        }
    }
    else if(type==BREATHDIFF)
    {
        QMapIterator<QString,QString> iter(breathDiffFatherItem_Map);
        while(iter.hasNext())
        {
            iter.next();
            QTreeWidgetItem *fatherItem=new QTreeWidgetItem(this);
            fatherItem->setText(0,iter.value());
            fatherItem_map.insert(iter.key(),fatherItem);
        }
        for(int i=0;i<lstDiffSound.size();i++)
        {
             diffSound diffsound=lstDiffSound.at(i);
             if(diffsound.m_strType==QString("1"))
             {
                addDiffSoundChild(fatherItem_map.find(diffsound.m_strGroupId).value(),diffsound);
             }

        }
    }
}
void qFlashTreeBase::addDiffSoundChild(QTreeWidgetItem *fatherItem,const diffSound &Data)
{
    //-----------------------子节点
    QTreeWidgetItem *item=new QTreeWidgetItem(fatherItem);
    item->setText(0,Data.m_strSoundName);
    item->setSizeHint(0,QSize(9000,35));
    TreeItemWidget *ItemWidget=new TreeItemWidget(this,TreeItemWidget::DiffSoundWidget);
    Treewidget_map.insert(Data.m_strId,ItemWidget);
    ItemWidget->setBtnData(Data.m_strId);
    this->setItemWidget(item,0,ItemWidget);
    connect(ItemWidget,SIGNAL(btnClickedtimes(QString &)),this,SLOT(DiffSoundItemClicked(QString &)));
    connect(this,SIGNAL(DiffSoundFull(bool)),ItemWidget,SLOT(DiffSoundFull(bool)));
    DiffSoundTreewidget_map.insert(ItemWidget->ID,Data);
}
void qFlashTreeBase::DiffSoundItemClicked(QString &ID)
{
    diffSound diffsound= DiffSoundTreewidget_map.find(ID).value();
    if(items>=2)
    {
        emit DiffSoundFull(false);
        QMessageBox::warning(this,QStringLiteral("添加提示"),QStringLiteral("一次只能添加2个"),QMessageBox::Yes);
        return;
    }
    emit DiffSound(diffsound);
    emit TreeItemWidgetID(diffsound.m_strId);
    items++;
}
void qFlashTreeBase::restoreTreeItemWidget(diffSound &Data)
{
    items--;
    emit DiffSoundFull(true);
    Treewidget_map.find(Data.m_strId).value()->restoreBtn();
}

//-------------------课件相关接口
void qFlashTreeBase::StartGetLocalCouseWare()
{
    QString CourseWareHLJson=QCoreApplication::applicationDirPath()+QString("/json/CourseWareHL.json");
    ReadJsonWorkhl->StartParseFile(CourseWareHLJson,&CourseWareHL_map);
    connect(ReadJsonWorkhl,SIGNAL(ParseFinish()),this,SLOT(GetLocalCouseWareABT()));

}
void qFlashTreeBase::GetLocalCouseWareABT()
{
     QString CourseWareABTJson=QCoreApplication::applicationDirPath()+QString("/json/CourseWareABT.json");
     ReadJsonWorkABT->StartParseFile(CourseWareABTJson,&CourseWareABT_map);
     connect(ReadJsonWorkABT,SIGNAL(ParseFinish()),this,SLOT(GetLocalCouseWareECG()));

}
void qFlashTreeBase::GetLocalCouseWareECG()
{
    QString CourseWareECGJson=QCoreApplication::applicationDirPath()+QString("/json/CourseWareECG.json");
    ReadJsonWorkECG->StartParseFile(CourseWareECGJson,&CourseWareECG_map);
    connect(ReadJsonWorkECG,SIGNAL(ParseFinish()),this,SLOT(GetCustomCouseDataFinsh()));
}

void qFlashTreeBase::setCouseWare(CourseWareType type)
{
    this->clear();
    CouseWareStyleSheet();
    this->setIndentation(20);
    this->setColumnWidth(1,46);
    this->setColumnWidth(0,204);
    if(type==HeartLungCourse)
    {
        QMapIterator<QString, QCoursewareInfo> map(CourseWareHL_map);
        constructionCouseWareTree(map);
        this->expandAll();
//        if(DefaultPtr!=Q_NULLPTR)
//        {
//            this->setCurrentItem(DefaultPtr);
//        }
    }
    else if(type==ABTCourse)
    {
        QMapIterator<QString, QCoursewareInfo> map(CourseWareABT_map);
        constructionCouseWareTree(map);
        this->expandAll();
//        if(DefaultPtr!=Q_NULLPTR)
//        {
//            this->setCurrentItem(DefaultPtr);
//        }
    }
    else if(type==ECGCourse)
    {
        QMapIterator<QString, QCoursewareInfo> map(CourseWareECG_map);
        constructionCouseWareTree(map);
        this->expandAll();
//        if(DefaultPtr!=Q_NULLPTR)
//        {
//            this->setCurrentItem(DefaultPtr);
//        }
    }
    SetCustomcoursewareTree(type);
}
void qFlashTreeBase::constructionCouseWareTree(QMapIterator<QString, QCoursewareInfo> &map)
{
   QMap<QString,QTreeWidgetItem*> Item_map;//存储父节点
    while (map.hasNext())
    {
        map.next();
        int count=map.key().count(QString("/"));
        if(count==1)
        {
           QTreeWidgetItem *item=new QTreeWidgetItem(this);
           item->setData(0,Qt::UserRole,QVariant::fromValue(map.value()));
           item->setData(0,Qt::UserRole+1,QString("local"));
           item->setData(0,Qt::UserRole+2,QString("Coursewar"));
           item->setData(1,Qt::UserRole+2,QString("Coursewar"));
           item->setText(0,map.value().m_strCoursewareName);
           Item_map.insert(map.key(),item);
        }
        if(count>1)
        {
           if(Item_map.find(map.key().section("/",0,count-1)).value()!=Q_NULLPTR)
           {
                QTreeWidgetItem *item=new QTreeWidgetItem( Item_map.find(map.key().section("/",0,count-1)).value());
                item->setData(0,Qt::UserRole,QVariant::fromValue(map.value()));
                item->setData(0,Qt::UserRole+1,QString("local"));
                item->setData(0,Qt::UserRole+2,QString("Coursewar"));
                item->setData(1,Qt::UserRole+2,QString("Coursewar"));
                item->setText(0,map.value().m_strCoursewareName);
                Item_map.insert(map.key(),item);
                if(map.value().m_strTreeDir==m_default)
                {
                    Default=map.value();
//                    DefaultPtr=item;
                }
           }
        }
     }
    GetSonNum();
}
void qFlashTreeBase::GetCustomCouseDataFinsh()
{
        ReadJsonWorkhl->deleteLater();
        ReadJsonWorkABT->deleteLater();
        ReadJsonWorkECG->deleteLater();
}
void qFlashTreeBase::GetCustomCourseWareData(QByteArray &Data)
{
     QParseInfoFromWeb parseCutsomCourse;
     parseCutsomCourse.ParseUsedefineCousewareInfo(Data,&lstUserCourseware);
}
void qFlashTreeBase::SetCustomcoursewareTree(CourseWareType type)
{
   if(lstUserCourseware.size()==0)
   {
        qDebug()<<"No CutomCouserware"<<"+++++++++++++++++++++++++++++++++++++++++";
        return;
   }
   QTreeWidgetItem *Customcourseware=new QTreeWidgetItem(this);
   Customcourseware->setData(0,Qt::UserRole+1,QString("custom"));
   Customcourseware->setData(0,Qt::UserRole+2,QString("Coursewar"));
   Customcourseware->setText(0,QStringLiteral("自定义课件"));
   userCourseware *m_CourseWare=Q_NULLPTR;
   if(type==HeartLungCourse)
   {
       QTreeWidgetItem *CUS_H_Item=new QTreeWidgetItem(Customcourseware);
       CUS_H_Item->setData(0,Qt::UserRole+1,QString("custom"));
       CUS_H_Item->setData(0,Qt::UserRole+2,QString("Coursewar"));
       CUS_H_Item->setText(0,QStringLiteral("心脏听诊"));
       QTreeWidgetItem *CUS_L_Item=new QTreeWidgetItem(Customcourseware);
       CUS_L_Item->setText(0,QStringLiteral("肺部听诊"));
       CUS_L_Item->setData(0,Qt::UserRole+1,QString("custom"));
       CUS_L_Item->setData(0,Qt::UserRole+2,QString("Coursewar"));
      for(int i=0;i<lstUserCourseware.size();i++)
      {
           m_CourseWare=lstUserCourseware.at(i);
           if(m_CourseWare->m_strType==QString("0"))
           {
               QTreeWidgetItem *Childitem=new QTreeWidgetItem(CUS_H_Item);
               Childitem->setText(0,m_CourseWare->m_strCoursewareName);
               Childitem->setData(0,Qt::UserRole,QVariant::fromValue((*m_CourseWare)));
               Childitem->setData(0,Qt::UserRole+1,QString("custom"));
               Childitem->setData(0,Qt::UserRole+2,QString("Coursewar"));
           }
           else if(m_CourseWare->m_strType==QString("1"))
           {
               QTreeWidgetItem *Childitem=new QTreeWidgetItem(CUS_L_Item);
               Childitem->setText(0,m_CourseWare->m_strCoursewareName);
               Childitem->setData(0,Qt::UserRole,QVariant::fromValue((*m_CourseWare)));
               Childitem->setData(0,Qt::UserRole+1,QString("custom"));
               Childitem->setData(0,Qt::UserRole+2,QString("Coursewar"));
           }
      }
   }
   else if(type==ABTCourse)
   {
       for(int i=0;i<lstUserCourseware.size();i++)
       {
           m_CourseWare=lstUserCourseware.at(i);
           if(m_CourseWare->m_strType==QString("2"))
           {
               QTreeWidgetItem *ChildItem=new QTreeWidgetItem(Customcourseware);
               ChildItem->setText(0,m_CourseWare->m_strCoursewareName);
               ChildItem->setData(0,Qt::UserRole,QVariant::fromValue((*m_CourseWare)));
               ChildItem->setData(0,Qt::UserRole+1,QString("custom"));
               ChildItem->setData(0,Qt::UserRole+2,QString("Coursewar"));
           }
       }
   }
   else if(type==ECGCourse)
   {

        for(int i=0;i<lstUserCourseware.size();i++)
        {
            m_CourseWare=lstUserCourseware.at(i);
            if(m_CourseWare->m_strType==QString("3"))
            {
                QTreeWidgetItem  *ChildItem=new QTreeWidgetItem(Customcourseware);
                ChildItem->setText(0,(m_CourseWare->m_strCoursewareName));
                ChildItem->setData(0,Qt::UserRole,QVariant::fromValue((*m_CourseWare)));
                ChildItem->setData(0,Qt::UserRole+1,QString("custom"));
                ChildItem->setData(0,Qt::UserRole+2,QString("Coursewar"));
            }
        }

   }
}
void qFlashTreeBase::CouseWareStyleSheet()
{
    this->setStyleSheet(QString("QTreeView::branch:has-siblings:!adjoins-item{border-image: url(:/images/vline.png) 0;}"
                                "QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/branch-more.png) 0;}"
                                "QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/branch-end.png) 0;}"
                                "QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/coursewarelist_more_button.png);}"
                                "QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/coursewarelistm_retract_button.png);}"
                                "QTreeView::item:hover{background-color:#4aabe9;}"
                                "QTreeView::item{margin-top:5px;}"
                                " color: white;"));
}


//------------------Item点击槽函数
void qFlashTreeBase::doItemClicked(QTreeWidgetItem *item, int colum)
{

//   this->expandItem(item);
//    item->setExpanded();
   QString data0 =item->data(0,Qt::UserRole+2).toString();
   QString data1 =item->data(1,Qt::UserRole+2).toString();
   /*****************点击课件Item*****************/
   if(data0==QString("Coursewar")||data1==QString("Coursewar"))
   {
       if(item->data(0,Qt::UserRole+1).toString()==QString("custom"))
       {
           QVariant data= item->data(0,Qt::UserRole);
           userCourseware info=data.value<userCourseware>();
           emit webItemData(info);
//           return;
       }
       else if(item->data(0,Qt::UserRole+1).toString()==QString("local"))
       {
           QVariant variant = item->data(0,Qt::UserRole);
           QCoursewareInfo info= variant.value<QCoursewareInfo>();
           if(!info.m_CaseID.isEmpty())
           {
               m_CaseIDMsg=info.m_strTreeDir+QString(":")+info.m_CaseID;
           }
           emit FlahsItemData(info);
//           return;
       }
   }
   /*********************点击病例Item**************************/
   else if(data0==QString("Case")||data1==QString("Case"))
   {

      stardardCase m_case=item->data(0,Qt::UserRole).value<stardardCase>();
//      QString m_ID=QString::number(colum)+QString(":")+m_case.m_strCaseId;
//      if(!m_case.m_strCaseId.isEmpty())
//      {
////        emit AllTeachCaseItem(m_ID);
//      }
       TreeItemWidget *widget=static_cast<TreeItemWidget *>(this->itemWidget(item,1));
         if(widget==Q_NULLPTR)
         {
             return;
         }
         else if(widget!=Q_NULLPTR)
         {
            QMapIterator<QString,TreeItemWidget*> iter(TreeItemWidget_map);
            if(colum==0)
            {
                while(iter.hasNext())
                {
                   iter.next();
                   iter.value()->changStyle(QString(""));
                   iter.value()->Casecolum0Clicked=false;
                }
              widget->changStyle(QString("QLabel{border-style:solid;border:1px solid #999999;border-radius:4px}"));
              widget->Casecolum0Clicked=true;
            }
            if(colum==1)
            {
                if(widget->Casecolum0Clicked)
                {
                    widget->changStyle(QString("QLabel{border-style:solid;border:1px solid #999999;background-color:#3099e5;border-radius:4px}"));
                    //病例Itme信号
                    emit CaseItemData(m_case);//发送Item 点击信息

                }
//                else
//                {
//                    return;
//                }
            }
         }
   }
   if(item->childCount()!=0)
   {
       bool expandll=item->isExpanded();
       if(expandll)
       {
           item->setExpanded(false);
       }
       if(!expandll)
       {
           item->setExpanded(true);
       }

   }

}

void qFlashTreeBase::OnTreeCtrlScroll(int n)
{
     Q_UNUSED(n);
     this->header()->resizeSection(0,220+this->horizontalScrollBar()->value());
     this->header()->resizeSection(2,m_nMaxTreeCoursewareLen-220-this->horizontalScrollBar()->value());
}

void qFlashTreeBase::GetSonNum()
{
    QTreeWidgetItemIterator  it (this);
    while (*it)
    {
        int count=(*it)->childCount();
        if(count!=0)
        {
            QString num=QString::number(GetAllSonNum((*it)));
            QString str=QString("(")+num+QString(")");
            (*it)->setText(1,str);
        }
        it++;
    }
}
int qFlashTreeBase::GetAllSonNum(QTreeWidgetItem *item)
{
    int aa=0;
    aa +=item->childCount();
    int cc=0;
    for(int i=0;i<aa;i++)
    {
      cc += GetAllSonNum(item->child(i));
    }
    return aa+cc;
}



