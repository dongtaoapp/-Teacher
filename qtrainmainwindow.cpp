#include "qtrainmainwindow.h"
#include "ui_qtrainmainwindow.h"
#include "define.h"
#include"qcomorder.h"
#include <QString>
#include <QFile>
#include <QRect>
#include <QPainter>
#include <qDebug>
#include <QPropertyAnimation>
#include<windows.h>
#include<QScrollbar>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>
#include <QFileInfo>
#include <QMessageBox>
#include <QDesktopWidget>
QString string111;
void parentExpand(QTreeWidgetItem *item)
{
    if(item->parent()!=Q_NULLPTR)
    {
        QTreeWidgetItem *pItem = item->parent();
        if (! pItem->isExpanded())
        {
           pItem->setExpanded(true);
        }
         parentExpand(pItem);
    }
    else
    {
        return;
    }
}
/****************搜素框**********************/

m_searchLineEdit::m_searchLineEdit(QWidget *parent):
    QWidget(parent)
{
    issearch=false;

    m_pSearchLineEdit = new QLineEdit(this);
    m_pSearchLineEdit->setObjectName("m_pSearchLineEdit");
    m_pSearchLineEdit->resize(228,26);
    pSearchButton = new QPushButton(this);
    pSearchButton->setObjectName("pSearchButton");
    pSearchButton->setCursor(Qt::PointingHandCursor);
    pSearchButton->setFixedSize(22, 26);
    pSearchButton->setToolTip(QStringLiteral("搜索"));


    //防止文本框输入内容位于按钮之下
    QMargins margins = m_pSearchLineEdit->textMargins();
    m_pSearchLineEdit->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
    m_pSearchLineEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));

    pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(pSearchButton);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    m_pSearchLineEdit->setLayout(pSearchLayout);
    connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(onSearch()));
}
m_searchLineEdit::~m_searchLineEdit()
{
    this->deleteLater();
    //delete search_btn;
}

void m_searchLineEdit::onSearch()
{
   QString str=m_pSearchLineEdit->text();
   if(!issearch)
   {
        issearch=true;
        pSearchButton->setStyleSheet(QString("image:url(:/images/cancelSearch.png)"));
        emit search(str);
   }
   else if(issearch)
   {
        issearch=false;
        pSearchButton->setStyleSheet(QString("image:url(:/images/search_button.png)"));
        m_pSearchLineEdit->clear();
        emit search(QString("RESET"));
   }

}
/*****************主界面****************************/
QTrainMainWindow::QTrainMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTrainMainWindow)
{
    ui->setupUi(this);
    ui->IdentifyauscultationBtn->hide();
    this->setObjectName("QTrainMainWindow");
    this->resize(WINDOWWIDTH,WINDOWHEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    m_play=false;
    is_soundPlay=false;
    is_listen=false;
    isloadflash=false;
    Synchronous=false;
    m_test=false;


    CurriculumID=QString("-1");
    comboID=-1;
    CurrentBtnIndex=-1;
    this->windowInit();

    compareview=new QCompareView(this);
    compareview->move(380,71);
    compareview->hide();
    sheduleView=new QChoseCurriculumView;
    talkwindow=new TalkbackView;

    QSettings *readconfig=new QSettings(APPPATH,QSettings::IniFormat);
    if(readconfig->value("System_Param/deskNumber").toInt()!=talkwindow->m_tabnum)
    {
        talkwindow->setTablenum( readconfig->value("System_Param/deskNumber").toInt());
        webIP=readconfig->value("System_Param/WebIP").toString();
    }
    delete readconfig;
    loadqss();
    m_manager.speakAndlistenInit();//初始化对话
    connect(m_close_btn,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    connect(m_min_btn,SIGNAL(clicked()),this,SLOT(showMinimized()));
    connect(talk_btn,SIGNAL(clicked()),this,SLOT(ontalkbtn()));
    connect(play_btn,SIGNAL(clicked()),this,SLOT(onPlaybtn()));
    connect(teach_btn,SIGNAL(clicked(bool)),this,SLOT(onTeachBtn()));
    connect(flash_widget,SIGNAL(FSCommand(QString,QString)),this,SLOT(flashAction(QString,QString)));
    connect(ui->IdentifyauscultationBtn,SIGNAL(clicked(bool)),compareview,SLOT(show()));
    connect(sheduleBtn,SIGNAL(clicked(bool)),sheduleView,SLOT(exec()));
    connect(sheduleView,SIGNAL(CLNum(ClassScheduleData &)),this,SLOT(setCurriculumID(ClassScheduleData &)));
    connect(sysTemBtn,SIGNAL(clicked(bool)),systemView,SLOT(show()));

    //-------------------
    connect(systemView,SIGNAL(onSetSystemCloseComputer()),&m_manager,SLOT(closeClientWindow()));
    connect(systemView,SIGNAL(pattern(QString)),&m_manager,SLOT(pattern(QString)));

    connect(touchTrain,SIGNAL(onitemClicked(QString &,int)),this,SLOT(PalpationTraining(QString &,int)));
    connect(this,SIGNAL(LocalPath(QString &)),this,SLOT(setPathshow(QString&)));
    //-------------------套餐信号槽
    connect(CourseWarecomboBtn,SIGNAL(checkedChanged(bool)),this,SLOT(OnCourseWarecomboBtn(bool)));
    connect(CaseconboBtn,SIGNAL(checkedChanged(bool)),this,SLOT(OnCaseComboBtn(bool)));
    connect(DiffconBtn,SIGNAL(checkedChanged(bool)),this,SLOT(OnDiffComboBtn(bool)));



    /*********对讲界面与Qmanager*************/
    connect(&m_manager,SIGNAL(ClientState(int,int)),talkwindow,SLOT(setTestbedState(int,int)));
    connect(talkwindow,SIGNAL(changTalkBntIcon()),this,SLOT(doChangTalkBntIcon()));
    connect(talkwindow,SIGNAL(allowTalkList(QList<int>,bool)),&m_manager,SLOT(doAllowTalk(QList<int>,bool)));
    connect(talkwindow,SIGNAL(doquit(bool)),&m_manager,SLOT(controllisten(bool)));
     connect(&m_manager,SIGNAL(ClientState(int,int)),this,SLOT(doRequest(int,int)));
    /*************main tab信号槽*********************/
    connect(&baseTree,SIGNAL(FlahsItemData(QCoursewareInfo&)),this,SLOT(OnFlashItemData(QCoursewareInfo&)));
    connect(&baseTree,SIGNAL(webItemData(userCourseware &)),this,SLOT(OnwebItemData(userCourseware &)));
    connect(&baseTree,SIGNAL(CaseItemData(stardardCase &)),this,SLOT(OnCaseItemData(stardardCase&)));
    connect(&baseTree,SIGNAL(DiffSound(diffSound&)),this,SLOT(OnDiffSoundData(diffSound &)));
    connect(&baseTree,SIGNAL(TreeItemWidgetID(QString &)),this,SLOT(AllTeachDiffItemWidgetID(QString &)));
    connect(&baseTree,SIGNAL(AllTeachCaseItem(QString &)),this,SLOT(AllTeachLocalCase(QString &)));
    connect(m_tab,SIGNAL(currentChanged(int)),this,SLOT(onTabchange(int)));
    connect(m_tab,SIGNAL(onClickedevent(int)),this,SLOT(onTabBtnClicked(int)),Qt::DirectConnection);

    connect(compareview,SIGNAL(CompareBntCilcked(diffSound &,diffSound &)),this,SLOT(StartCompareSound(diffSound &,diffSound &)));

    connect(compareview,SIGNAL(deleteDiffSound1(diffSound &)),this,SLOT(CompareItem1(diffSound&)));
    connect(compareview,SIGNAL(deleteDiffSound2(diffSound &)),this,SLOT(CompareItem2(diffSound&)));
//restoreTreeItemWidget(diffSound &) baseTree


/****************搜索信号槽*******************/
    connect(searchEdit,SIGNAL(search(QString&)),this,SLOT(doSearchWork(QString&)));


/******************web信号槽*************************/
    //----------------------获取自定义课件
    connect(&webmanager,SIGNAL(CustomCourseData(QByteArray &)),this,SLOT(CouseWareTreeWidgetInit(QByteArray &)));

    //-------------------全部鉴别听诊
    connect(&webmanager,SIGNAL(DiffSoundData(QByteArray &)),this,SLOT(DiffTreeWidgetInit(QByteArray&)));
    connect(&webmanager,SIGNAL(DiffSoundData(QByteArray &)),this,SLOT(GetCustomWare()));

    //----------------鉴别听诊声音
    connect(&webmanager,SIGNAL(DiffSoundFileData(QByteArray &)),this,SLOT(DiffSoundLoadInit(QByteArray &)));

    m_pSoundControl = NULL;
    m_nDelayHandle = 0;
    m_nState = 0;
    m_comReadArray.clear();
    //初始化串口
    InitComm();
    connect(speak_btn,SIGNAL(clicked()),this,SLOT(OnSoundPlay()));
    connect(listen_btn,SIGNAL(clicked()),this,SLOT(OnSoundSimular()));
}

QTrainMainWindow::~QTrainMainWindow()
{
    if(m_nDelayHandle != 0)
        killTimer(m_nDelayHandle);
    m_pSerialPort->close();
    delete ui;
    delete talkwindow;
    delete sheduleView;
    delete touchTrain;
    if(m_pSoundControl != NULL)
    {
        delete m_pSoundControl;
    }
    qDebug()<<__FUNCTION__;
}

void QTrainMainWindow::loadqss()
{
    QFile file(":/qss/PhysicalCheckTrainTeacher.qss");
    if(file.open(QFile::ReadOnly))
    {
      QString str;
      str.prepend(file.readAll());
      this->setStyleSheet(str);
    }
    file.close();
}

void QTrainMainWindow::InitShow()
{
    this->show();
    this->InitSoundControl();
}

void QTrainMainWindow::flashAction(QString cmd, QString data)
{
    qDebug()<<__FUNCTION__<<cmd<<data;
    flash_widget->StartPlay();
    play_btn->setStyleSheet("border-style:none;image:url(:/images/play_button_presed.png)");
    m_play=true;
    if(is_listen)
    {
        m_nState=2;
        OnSoundSimular();
    }
    if(is_soundPlay)
    {
        play();
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
        is_soundPlay=false;
    }
}
/**********控件初始化 位置 大小******************/
void QTrainMainWindow::windowInit()
{

    stacked_tree=new QStackedWidget(this);
    stacked_tree->setGeometry(124,71,258,636);
    stacked_tree->insertWidget(ID_HS_CWARE,&baseTree);
    m_tab=new main_tab(this);
    m_tab->setObjectName("m_tab");
    m_tab->setGeometry(0,70,124,669);
    m_tab->setTypeFoucse(main_tab::CouswareFoucse,0);
    baseTree.setCouseWare(qFlashTreeBase::HeartLungCourse);

    top_label=new QLabel(this);
    top_label->setObjectName("top_label");
    top_label->setGeometry(0,0,1366,25);

    m_title_label=new QLabel(this);
    m_title_label->setObjectName("m_title_label");
    m_title_label->setGeometry(11,7,270,12);
    m_title_label->setText(QString(QStringLiteral("体格检查云平台——课件教学软件教师机 版本%1")).arg("v1.1"));

    m_log_label=new QLabel(this);
    m_log_label->setGeometry(0,25,124,46);
    m_log_label->setObjectName("m_log_title");

    m_min_btn=new QPushButton(this);
    m_min_btn->setCursor(Qt::PointingHandCursor);
    m_min_btn->setObjectName("m_min_btn");
    m_min_btn->setGeometry(1303,0,30,25);
    m_close_btn=new QPushButton(this);
    m_close_btn->setCursor(Qt::PointingHandCursor);
    m_close_btn->setObjectName("m_close_btn");
    m_close_btn->setGeometry(1336,0,30,25);

    play_btn=new QPushButton(this);
    play_btn->setObjectName("play_btn");
    play_btn->setGeometry(1282,142,44,44);
    play_btn->setCursor(Qt::PointingHandCursor);
    play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
    play_btn->setEnabled(false);
    play_label=new QLabel(this);
    play_label->setGeometry(1288,197,31,12);
    play_label->setText(QStringLiteral("播 放"));


    listen_btn = new QPushButton(this);
    listen_btn->setObjectName("listen_btn");
    listen_btn->setGeometry(1282,233,44,44);
    listen_btn->setCursor(Qt::PointingHandCursor);
    listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png_gray.png)"));
    listen_btn->setEnabled(false);
    listen_label=new QLabel(this);
    listen_label->setGeometry(1288,288,32,12);
    listen_label->setText(QStringLiteral("听 诊"));

    speak_btn=new QPushButton(this);
    speak_btn->setGeometry(1282,324,44,44);
    speak_btn->setObjectName("speak_btn");
    speak_btn->setCursor(Qt::PointingHandCursor);
    speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
    speak_btn->setEnabled(false);
    speak_label=new QLabel(this);
    speak_label->setGeometry(1280,378,48,12);
    speak_label->setText(QStringLiteral("扩音听诊"));

    talk_btn=new QPushButton(this);
    talk_btn->setObjectName("talk_btn");
    talk_btn->setGeometry(1282,416,44,44);
    talk_btn->setCursor(Qt::PointingHandCursor);
    talk_label=new QLabel(this);
    talk_label->setGeometry(1288,469,32,12);
    talk_label->setText(QStringLiteral("对 讲"));

    teach_btn=new QPushButton(this);
    teach_btn->setObjectName("teach_btn");
    teach_btn->setGeometry(1282,507,44,44);
    teach_btn->setCursor(Qt::PointingHandCursor);
    teach_label=new QLabel(this);
    teach_label->setGeometry(1281,560,47,12);
    teach_label->setText(QStringLiteral("全体教学"));

    search_label=new QLabel(this);
    search_label->setObjectName("search_label");
    search_label->setGeometry(124,25,258,46);
    local_label=new QLabel(this);
    local_label->setObjectName("local_label");
    local_label->setGeometry(382,25,984,46);

    path_label=new QLabel(this);
    path_label->setObjectName("path_label");
    path_label->setGeometry(397,41,700,14);

    bottom_label=new QLabel(this);
    bottom_label->setObjectName("bottom_label");
    bottom_label->setAlignment(Qt::AlignCenter);
    bottom_label->setText(QStringLiteral("2017-2020 JYYXCopyRight.all right reservesed"));
    bottom_label->setGeometry(0,740,1366,28);

    touchTrainLabel=new QLabel(QStringLiteral("触诊练习"),this);
    touchTrainLabel->hide();
    touchTrainLabel->setObjectName("touchTrainLabel");
    touchTrainLabel->setGeometry(1017,42,62,15);

    /***********头像**********/
    image_label=new QLabel(this);
    image_label->setObjectName("image_label");
    image_label->setGeometry(1255,32,23,33);


    searchEdit=new m_searchLineEdit(this);
    searchEdit->setGeometry(133,34,228,26);

    flash_widget=new QMAxWidget(this);
    flash_widget->setGeometry(406,98,844,642);
    flash_widget->hide();

    web_PPt=new QWebEngineView(this);
    web_PPt->setGeometry(406,98,844,642);
    web_PPt->hide();



    sheduleBtn=new QPushButton(this);
    sheduleBtn->setObjectName("sheduleBtn");
    sheduleBtn->setCursor(Qt::PointingHandCursor);
    sheduleBtn->setToolTip(QStringLiteral("选择课程"));
    sheduleBtn->setGeometry(1190,36,26,24);

    /**********设置按钮*********/
    sysTemBtn=new QPushButton(this);
    sysTemBtn->setCursor(Qt::PointingHandCursor);
    sysTemBtn->setObjectName("sysTemBtn");
    sysTemBtn->setGeometry(1290,43,40,10);

    touchTrain=new QTouchTrainView;
    touchTrainBtn=new QPushButton(this);
    touchTrainBtn->hide();
    touchTrainBtn->setObjectName("touchTrainBtn");
    touchTrainBtn->setCursor(Qt::PointingHandCursor);
    touchTrainBtn->setGeometry(986,34,22,26);
    touchTrainBtn->setMenu(touchTrain);

   systemView=new QSetSystemView(this);
   systemView->move(1180,80);
   systemView->hide();

   TipBox=new QPalpationpracticeTip(this);


   CourseWarecomboBtn= new SwitchButton(this);
   CourseWarecomboBtn->setGeometry(137,709,232,32);
   CourseWarecomboBtn->setText(QStringLiteral("课件套餐"),QStringLiteral("全部课件"));

   CaseconboBtn= new SwitchButton(this);
   CaseconboBtn->setGeometry(137,709,232,32);
   CaseconboBtn->setText(QStringLiteral("病例套餐"),QStringLiteral("全部病例"));
   CaseconboBtn->hide();

   DiffconBtn= new SwitchButton(this);
   DiffconBtn->setGeometry(137,709,232,32);
   DiffconBtn->setText(QStringLiteral("课件套餐"),QStringLiteral("全部套餐"));
   DiffconBtn->hide();
}

void QTrainMainWindow::CouseWareTreeWidgetInit(QByteArray &Data)
{

    //自定义课件
//   qDebug()<<__FUNCTION__<<Data;

//    QString str= QStringLiteral("[{\"custom_course_id\":\"3\","
//                                "\"course_name\": \"课件1\",\"course_type\": \"0\","
//                                "\"course_file\": \"/ViewerJS/#../files/attach/1667.odb\"},"
//                                "{\"custom_course_id\": \"5\",\"course_name\": " "\"课件2\","
//                                "\"course_type\": " "\"1\",\"course_file\": \"/ViewerJS/#.."
//                                "/files/attach/2017.odb\"}]");
//    QByteArray data11 = str.toUtf8();

    baseTree.GetCustomCourseWareData(Data);

}

void QTrainMainWindow::DiffTreeWidgetInit(QByteArray &data)
{
//   qDebug()<<__FUNCTION__<<data;

//  QString str=QStringLiteral("[{\"discern_id\": \"1\",\"discern_name\": "
//               "\"测试心音鉴别听诊套餐\",\"organ_type\":"
//               " \"0\",\"if_use\": \"1\",\"sound_list\": "
//               "[{\"sound_file\": \"files/attach/images/content/20170803/15017257768026.wav\",\"organ_type\": "
//               "\"0\",\"case_id\": \"6\",\"case_name\": \"成人测试2\"},{\"sound_file\": "
//               "\"files/attach/images/content/20170802/15016516122029.wav\",\"organ_type\": "
//               "\"0\",\"case_id\": \"2\",\"case_name\": \"测试心音2\"}]},{\"discern_id\": \"2\",\"discern_name\": "
//               "\"测试呼吸音鉴别听诊套餐33\",\"organ_type\": \"1\",\"if_use\": \"0\",\"sound_list\": [{\"sound_file\": "
//               "\"files/attach/images/content/20170802/15016518174065.wav\",\"organ_type\": \"1\",\"case_id\": "
//               "\"3\",\"case_name\": \"测试呼吸音\"}]}]");

//    QByteArray data111=str.toUtf8();
    baseTree.GetDiffSoundData(data);

}


void QTrainMainWindow::loadflash(QString &flashpath)
{
    m_flashpath.clear();
    m_flashpath=flashpath;
    flash_widget->loadFlash(m_flashpath);
    isloadflash=true;
    m_play=false;

}
/***********flash play pause**************/
void QTrainMainWindow::onPlaybtn()
{
    if(Synchronous)
    {
       m_manager.ALLTeachWork(QString("play"));
       Synchronous=false;
       m_test=true;
    }
    if(is_listen)
    {
        m_nState=2;
        OnSoundSimular();
    }
    if(is_soundPlay)
    {
        play();
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
        is_soundPlay=false;
    }
    if(m_test)
    {
        Synchronous=true;
    }
    if(m_flashpath.isEmpty())
    {
        return;
    }
    if(m_play)
    {
        flash_widget->PausePlay();
        play_btn->setStyleSheet("border-style:none;image:url(:/images/play_button.png)");
        m_play=false;
        return;
    }
    else if(!m_play)
    {
        flash_widget->StartPlay();
       play_btn->setStyleSheet("border-style:none;image:url(:/images/play_button_presed.png)");
       m_play=true;
       return;
    }

}


void QTrainMainWindow::ontalkbtn()
{
    QSettings *readconfig=new QSettings(APPPATH,QSettings::IniFormat);
    if(readconfig->value("System_Param/deskNumber").toInt()!=talkwindow->m_tabnum)
    {
        qDebug()<<__FUNCTION__<<"changing tablenum is :"<< readconfig->value("System_Param/deskNumber").toInt();
        talkwindow->setTablenum( readconfig->value("System_Param/deskNumber").toInt());
    }
    delete readconfig;
    talkwindow->exec();
}

void QTrainMainWindow::onTeachBtn()
{
    if(!Synchronous)
    {
        m_tab->setCurrentIndex(MAIN_TAB_CO);
        m_tab->setTypeFoucse(main_tab::CouswareFoucse,0);
        baseTree.setCouseWare(qFlashTreeBase::HeartLungCourse);
        m_manager.startAllTeach(true);
        Synchronous=true;
        compareview->setEmpityBtnWork(false);
        teach_btn->setStyleSheet(QString("image:url(:/images/allTeach_ing.png)"));
        qDebug()<<__FUNCTION__<<"++++++++++++++"<<Synchronous;
        return;
    }
    if(Synchronous)
    {
        m_manager.startAllTeach(false);
        compareview->setEmpityBtnWork(true);
        Synchronous=false;
        m_test=false;
        teach_btn->setStyleSheet(QString("image:url(:/images/wholeteaching_button.png)"));
        qDebug()<<__FUNCTION__<<"++++++++++++++"<<Synchronous;
        return;
    }



}
/***********索搜***************/
void QTrainMainWindow::doSearchWork(QString &str)
{
   if(str.isEmpty()&&str!=QString("RESET"))
   {
       return;
   }
    int index=m_tab->currentIndex();

        QTreeWidget *basetree= static_cast<QTreeWidget*>(stacked_tree->currentWidget());
        QTreeWidgetItem *pItem=Q_NULLPTR;
        if(str==QString("RESET"))
        {
            QTreeWidgetItemIterator it(basetree);
            while(*it)
            {
                if(-1 != (*it)->text(0).indexOf(string111))
                {
                    if(index==MAIN_TAB_CO)
                    {
                        (*it)->setBackground(0,Qt::color0);
                    }
                    else if(index==MAIN_TAB_CA||index==MAIN_TAB_AU)
                    {
                        (*it)->setBackground(0,Qt::color0);
                        basetree->setStyleSheet(QString("QTreeView::item:selected{color:green;}"
                                                        "QTreeView::item{border-style:sold;border-bottom:1px solid #bebebe;}"));;
                    }
                }
                it++;
            }
        }
        if(!str.isEmpty()&&str!=QString("RESET"))
        {
            string111=str;
            QTreeWidgetItemIterator it(basetree);
            while (*it)
            {
                if(-1 != (*it)->text(0).indexOf(str))
                {

                    if(index==MAIN_TAB_CO)
                    {
                        pItem = (*it)->parent();
                        if (pItem !=Q_NULLPTR)
                        {
                            bool isExpanded = pItem->isExpanded();
                            if (! isExpanded)
                            {
                                basetree->expandItem(pItem);
                            }
                        }
                        (*it)->setBackground(0,Qt::green);
                        parentExpand(*it);
                    }
                    else if(index==MAIN_TAB_CA||index==MAIN_TAB_AU)
                    {
                       basetree->setStyleSheet(QString(" "));
                       (*it)->setBackground(0,Qt::green);
                       parentExpand(*it);
                    }
                }
            it++;
            }
        }
}


void QTrainMainWindow::ChangeTabStyleSheet(int index)
{
        if(index==0)
        {
             web_PPt->hide();
             flash_widget->show();
             play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
             play_btn->setEnabled(false);
             listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png_gray.png)"));
             speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
             listen_btn->setEnabled(false);
             speak_btn->setEnabled(false);
        }
        if(index==1||index==2)
        {
             if(isloadflash)
             {
                 flash_widget->PausePlay();
                loadflash(QString("reset"));
                isloadflash=false;
             }
             if(!web_PPt->isHidden())
             {
                web_PPt->hide();
             }
             if(!flash_widget->isHidden())
             {
                flash_widget->hide();
             }
             listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png"));
             speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
             listen_btn->setEnabled(true);
             speak_btn->setEnabled(true);
             play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
             play_btn->setEnabled(false);
        }
}
void QTrainMainWindow::CourseWareTab()
{

    m_tab->setTypeFoucse(main_tab::CouswareFoucse,0);
    baseTree.setCouseWare(qFlashTreeBase::HeartLungCourse);

    CaseconboBtn->hide();
    DiffconBtn->hide();
    CourseWarecomboBtn->show();

}
void QTrainMainWindow::CaseTab()
{

    m_tab->setTypeFoucse(main_tab::CaseFoucse,0);
    baseTree.setCaseTree(qFlashTreeBase::CORDIOPHONY);
    CourseWarecomboBtn->hide();
    DiffconBtn->hide();

    CaseconboBtn->show();

}
void QTrainMainWindow::DiffTab()
{
    m_DiffsoundInfo[0].clear();
    m_DiffsoundInfo[1].clear();

    compareview->widgetinit();
    compareview->show();
    ui->IdentifyauscultationBtn->show();

    m_tab->setTypeFoucse(main_tab::DiffFoucse,0);
    baseTree.setDiffTree(qFlashTreeBase::HEARTDIFF);
    CourseWarecomboBtn->hide();
    CaseconboBtn->hide();

    DiffconBtn->show();

    if(DiffHavePackage)
    {
            //TODO
    }
}
void QTrainMainWindow::onTabchange(int index)
{
    ChangeTabStyleSheet(index);
    ui->IdentifyauscultationBtn->hide();
    compareview->hide();
    baseTree.clear();
    if(Synchronous)
    {
         m_manager.AllTeachActionTab(index);
    }
    if(m_nState==3)
    {
        m_pSoundControl->OnStopLoudAuscultate();
        m_nState = 0;
    }
    switch(index)
    {  
    case MAIN_TAB_CO:
        CourseWareTab();
        break;
    case MAIN_TAB_CA:
        CaseTab();
        break;
    case MAIN_TAB_AU:
        DiffTab();
        break;
    }

}

/************tab中按钮点击信号***************/
void QTrainMainWindow::onTabBtnClicked(int index)
{ 
    CurrentBtnIndex=index;
    //--------同步切换界面
    if(Synchronous)
    {
        m_manager.AllTeachActionBtn(QString::number(index));
    }

    /****************心肺听诊课件**************/
       if(index==ID_HS_CWARE)
       {
           baseTree.setCouseWare(qFlashTreeBase::HeartLungCourse);
       }
    /*********腹部听诊课件*********/
       if(index==ID_ABT_CWARE)
       {
           touchTrainBtn->show();
           touchTrainLabel->show();
           baseTree.setCouseWare(qFlashTreeBase::ABTCourse);
           return;
       }

    /***********心电图课件*******************/
       if(index==ID_ECG_CWARE)
       {
            baseTree.setCouseWare(qFlashTreeBase::ECGCourse);
       }
       touchTrainBtn->hide();
       touchTrainLabel->hide();



 /****************心音听诊病例*********************/
   if(index==ID_HS_ALL_CASE||index==ID_HS_ADULT_CASE||index==ID_HS_CHILD_CASE||index==ID_HS_OLD_CASE)
   {
         baseTree.setCaseTree(qFlashTreeBase::CORDIOPHONY);
   }
   if(index==ID_HS_ADULT_CASE)
   {
      baseTree.m_ShowHiden(1);
   }
   if(index==ID_HS_CHILD_CASE)
   {
      baseTree.m_ShowHiden(2);
   }
   if(index==ID_HS_OLD_CASE)
   {
      baseTree.m_ShowHiden(0);
   }

/***********腹部听诊病例*********************/

   if(index==ID_ABS_ALL_CASE||index==ID_ABS_OLD_CASE||index==ID_ABS_ADULT_CASE||index==ID_ABS_CHILD_CASE)
   {
         baseTree.setCaseTree(qFlashTreeBase::LUNGAUSCULTATION);
   }
   if(index==ID_ABS_ADULT_CASE)
   {
      baseTree.m_ShowHiden(1);
   }
   if(index==ID_ABS_CHILD_CASE)
   {
      baseTree.m_ShowHiden(2);
   }
   if(index==ID_ABS_OLD_CASE)
   {
      baseTree.m_ShowHiden(0);
   }

/**************肠鸣音听诊病例*********************/

   if(index==ID_BBGS_ALL_CASE||index==ID_BBGS_ADULT_CASE||index==ID_BBGS_CHILD_CASE||index==ID_BBGS_OLD_CASE)
   {
         baseTree.setCaseTree(qFlashTreeBase::Borborygmus);
   }
   if(index==ID_BBGS_ADULT_CASE)
   {
      baseTree.m_ShowHiden(1);
   }
   if(index==ID_BBGS_CHILD_CASE)
   {
      baseTree.m_ShowHiden(2);
   }
   if(index==ID_BBGS_OLD_CASE)
   {
      baseTree.m_ShowHiden(0);
   }


//-----------------鉴别听诊
   if(index==ID_HS_AUT||index==ID_BS_AUT)
   {
       compareview->widgetinit();
   }
   if(index==ID_HS_AUT)
   {
        baseTree.setDiffTree(qFlashTreeBase::HEARTDIFF);
   }
   if(index==ID_BS_AUT)
   {
       baseTree.setDiffTree(qFlashTreeBase::BREATHDIFF);
   }

}

void QTrainMainWindow::OnFlashItemData(QCoursewareInfo &info)
{
    //心电图 play listen speak 失效
//amplifyingauscultation_button.png_gray.png
    if(info.m_strFlash.isEmpty())
    {
        return;
    }


    if(info.m_sound_list.isEmpty())
    {
        listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png_gray.png)"));
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
        listen_btn->setEnabled(false);
        speak_btn->setEnabled(false);
    }
    else
    {
        listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png"));
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
        listen_btn->setEnabled(true);
        speak_btn->setEnabled(true);
    }
//    if(info.m_strFlash.isEmpty())
//    {
//        play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
//        play_btn->setEnabled(false);
//    }
//    else
//    {
        play_btn->setStyleSheet(QString("image:url(:/images/play_button.png)"));
        play_btn->setEnabled(true);
//    }
    if(CurrentBtnIndex==ID_ECG_CWARE)
    {
        listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png_gray.png)"));
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
        play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
        play_btn->setEnabled(false);
        listen_btn->setEnabled(false);
        speak_btn->setEnabled(false);
    }
    if(CurrentBtnIndex==ID_ABT_CWARE)
    {
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
        speak_btn->setEnabled(false);
    }
    if(flash_widget->isHidden())
   {
       flash_widget->show();
   }
    if(!web_PPt->isHidden())
   {
       web_PPt->hide();
   }

    QString path=QString(QStringLiteral("您所在的位置:%1")).arg(info.m_strTreeDir);
    emit LocalPath(path);
    if(Synchronous)
    {
      m_manager.ALLTeachLocalFlash(info.m_strTreeDir);
    }
    int count=info.m_strTreeDir.count(QString("/"));
    QString str=QString("file:///")+QCoreApplication::applicationDirPath()
           +QString("/")+QString("Resource")+info.m_strTreeDir.section("/",0,count-1)+QString("/")+info.m_strFlash;
    qDebug()<<str;
    loadflash(str);
    m_nState = 0;
    m_pSoundControl->LoadSoundConfigue(info.m_sound_list,info.m_tremble_position,info.m_defalut_sound);//初始化扩音听诊信息
}

void QTrainMainWindow::OnwebItemData(userCourseware &info)
{
    flash_widget->PausePlay();
    play_btn->setStyleSheet(QString("image:url(:/images/play_button_gray.png)"));
    listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png_gray.png)"));
    speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png_gray.png)"));
    listen_btn->setEnabled(false);
    speak_btn->setEnabled(false);
    play_btn->setEnabled(false);

    if(!flash_widget->isHidden())
    {
        flash_widget->hide();
    }
    if(web_PPt->isHidden())
    {
        web_PPt->show();
    }


    QString Path=QString(QStringLiteral("你所在的位置:自定义课件/%1")).arg(info.m_strCoursewareName);
    emit LocalPath(Path);
    QString http=QString("http://%1").arg(webIP)+info.m_strUrl;
    web_PPt->load(QUrl(http));
}

void QTrainMainWindow::OnCaseItemData(stardardCase &Case)
{
    qDebug()<<__FUNCTION__<<Case.m_default_sound<<Case.m_tremble;
    //----------------初始化扩音听诊 听诊按钮
    speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
    is_soundPlay=false;
    listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png"));
    is_listen=false;

    QString faDir,sonDir;
    int Type=Case.m_strType.toInt();
    int Hunman=Case.m_strHuman.toInt();
    switch(Type)
    {
    case 0:
        faDir=QString(QStringLiteral("心音听诊"));
        break;
    case 1:
        faDir=QString(QStringLiteral("呼吸音听诊"));
        break;
    case 2:
        faDir=QString(QStringLiteral("肠鸣音听诊"));
        break;
    }
    switch(Hunman)
    {
    case 0:
        sonDir=QString(QStringLiteral("儿童"));
        break;
    case 1:
        sonDir=QString(QStringLiteral("成人"));
        break;
    case 2:
        sonDir=QString(QStringLiteral("老人"));
        break;
    }
    QString path=QString(QStringLiteral("你所在的位置:标准化病例/%1/%2/%3")).arg(sonDir).arg(faDir).arg(Case.m_strName);
    emit LocalPath(path);
    m_nState = 0;
    m_pSoundControl->LoadSoundConfigue(Case.m_sound_list,Case.m_tremble,Case.m_default_sound);//初始化扩音听诊信息

}
void QTrainMainWindow::AllTeachLocalCase(QString &id)
{
    if(Synchronous)
    {
        m_manager.ALLTeachLocalCase(id);
    }
}

void QTrainMainWindow::setPathshow(QString &path)
{
    if(path.isEmpty())
    {
        return;
    }
    path_label->setText(path);
}

/************课程相关*****************/
void QTrainMainWindow::ClassScheduleInit()
{

    //-------------------测试数据

    ClassScheduleData Data1,Data2;
    Data1.ScheduleID="12";
    Data1.ScheduleName=QStringLiteral("正常呼吸音听诊");
    Data1.ScheduleTime="2017-9-27";
    Data1.ScheduleType="1";

    Data2.ScheduleID="13";
    Data2.ScheduleName=QStringLiteral("肺泡的结构与功能");
    Data2.ScheduleTime="2017-9-22";
    Data2.ScheduleType="0";

    sheduleView->addCurriculum(Data1);
    sheduleView->addCurriculum(Data2);
    sheduleView->show();

}



void QTrainMainWindow::setCurriculumID(ClassScheduleData &Data)
{

    CurriculumID=Data.ScheduleID;
    if(CurriculumID==QString("12"))
    {
        CourseWarecomboBtn->setChecked(false);
        CaseconboBtn->setChecked(false);
        DiffconBtn->setChecked(false);

    }
    if(CurriculumID==QString("13"))
    {
        CourseWarecomboBtn->setChecked(true);
        CaseconboBtn->setChecked(true);
        DiffconBtn->setChecked(true);

    }
    if(this->isHidden())
    {
        QDesktopWidget* desktop =qApp->desktop();
        move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
        this->show();
        this->InitSoundControl();
    }
}

//------------------课件 病例 鉴别 套餐
void QTrainMainWindow::OnCourseWarecomboBtn(bool checked)
{
    qDebug()<<__FUNCTION__;
}
void QTrainMainWindow::OnCaseComboBtn(bool checked)
{
    qDebug()<<__FUNCTION__;
}
void QTrainMainWindow::OnDiffComboBtn(bool checked)
{
    qDebug()<<__FUNCTION__;
}




void QTrainMainWindow::doLoginsuccess(QString &name, QString &avatar)
{

    this->sysTemBtn->setText(name);
    this->image_label->setAlignment(Qt::AlignCenter);
    this->image_label->setStyleSheet(QString("QLabel{border-radius:15px;background-color:red}"));
    this->image_label->setPixmap(QCoreApplication::applicationDirPath()+QString("/Avatar/talk_Btn_Request.png"));
}
void QTrainMainWindow::InitSoundControl()
{
    HWND hCurWnd = (HWND)winId();

    QSettings *readType=new QSettings(APPPATH,QSettings::IniFormat);
    qDebug()<<__FUNCTION__<<readType->value("System_Param/HeartAuscultateType").toBool()<<readType->value("System_Param/LoudSoundType").toBool();

//参数1:窗口句柄 参数2:路径 参数3:心音模拟听诊 参数4:心肺扩音听诊
    m_pSoundControl = new QSoundControl(hCurWnd,QCoreApplication::applicationDirPath(),
                                        readType->value("System_Param/HeartAuscultateType").toBool(),
                                        readType->value("System_Param/LoudSoundType").toBool());
   delete readType;


  //  QSettings *readType=new QSettings(APPPATH,QSettings::IniFormat);

//    m_pSoundControl = new QSoundControl(hCurWnd,QCoreApplication::applicationDirPath());

            //   delete readType;
}

void QTrainMainWindow::OnSoundPlay()
{
        if(Synchronous)
        {
            m_manager.ALLTeachWork(QString("phonophoresis"));
            Synchronous=false;
            m_test=true;
        }
        if(is_listen)
        {
            m_nState=2;
            OnSoundSimular();
        }
        if(m_play)
        {
           onPlaybtn();
        }
        if(m_test)
        {
            Synchronous=true;
        }
        play();

        if(!is_soundPlay)
        {
            speak_btn->setStyleSheet(QString("image:url(:/images/kuoyin_ing.png)"));
            is_soundPlay=true;
            return;
        }
        if(is_soundPlay)
        {
            speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
            is_soundPlay=false;
            return;
        }
}
void QTrainMainWindow::play()
{
    if(m_nDelayHandle == 0)
    {
         m_nDelayHandle = startTimer(200);
    }
}
void QTrainMainWindow::readyReadSlot()
{
    m_cComReadMutex.lock();
    m_comReadArray.append(m_pSerialPort->readAll());
    QComOrder comOrder;
    QList<comDataStruct*> lstdata;
    comOrder.ParseComReadData(m_comReadArray,lstdata);
    for (int i = 0; i < lstdata.size(); ++i)
    {
        comDataStruct* pData = lstdata.at(i);
        if(pData->m_nCmdType == 0)
            m_pSoundControl->OnAuscultatePosHandle(TRUE,pData->m_data[10]);
        else if(pData->m_nCmdType == 1)
        {
            //腹部触诊响应，关闭等待对话框
            TipBox->close();
        }
        delete pData;
    }
    m_cComReadMutex.unlock();
}

void QTrainMainWindow::OnSoundSimular()
{
    if(Synchronous)
    {
        m_manager.ALLTeachWork(QString("auscultation"));
        Synchronous=false;
        m_test=true;
    }
    if(is_soundPlay)
    {
        speak_btn->setStyleSheet(QString("image:url(:/images/amplifyingauscultation_button.png)"));
        is_soundPlay=false;
    }
    if(m_play)
    {
        onPlaybtn();
    }
    if(m_test)
    {
        Synchronous=true;
    }
    QComOrder comOrder;
    QByteArray data;
    if( 2 != m_nState)
    {
        listen_btn->setStyleSheet(QString("image:url(:/images/monitingzhen_ing.png)"));
        is_listen=true;
        //下发模拟听诊模式
        comOrder.GetTeachModeOrder(1,data);
        m_pSerialPort->write(data);
        m_nState = 2;
        //
        m_pSoundControl->OnSimulateAuscultateHandle();
        //发送震颤位置
        BYTE pos;
        m_pSoundControl->GetHeartVibrPosValue(&pos);
        comOrder.GetVidrPosOrder(pos,data);
        int aa=m_pSerialPort->write(data);
    }
    else
    {
        listen_btn->setStyleSheet(QString("image:url(:/images/auscultation_button.png)"));
        is_listen=false;
        //下发教学讲解模式
        comOrder.GetTeachModeOrder(0,data);
        m_pSerialPort->write(data);
        m_nState = 0;

        m_pSoundControl->OnStopSimulateAusculate();
        //发送停止震颤命令
        comOrder.GetStopVidrOrder(data);
        int cc=m_pSerialPort->write(data);
    }
}

void QTrainMainWindow::PalpationTraining(QString &text,int index)
{
    QComOrder comOrder;
    QByteArray data;
    comOrder.GetPalpateOrder(data,index-1);
    m_pSerialPort->write(data);
    TipBox->SetTitle(text);
    TipBox->m_exec();



}

void QTrainMainWindow::OnDiffSoundData(diffSound &diffsound)
{
    qDebug()<<__FUNCTION__<<diffsound.m_strId<<diffsound.m_strSoundName;
    webmanager.GetDiffSoundFile(diffsound.m_strId);
    compareview->addComopareMsg(diffsound);
}

void QTrainMainWindow::AllTeachDiffItemWidgetID(QString &ID)
{
    if(Synchronous)
    {
        m_manager.AllTeachActionDiffItem(ID);
    }
}


void QTrainMainWindow::StartCompareSound(diffSound &data1,diffSound &data2)
{
    Q_UNUSED(data1);
    Q_UNUSED(data2);
    m_nState = 0;
    m_pSoundControl->LoadDiffSoundConfigue(m_DiffsoundInfo[0],m_DiffsoundInfo[1]);
    if(Synchronous)
    {
        m_manager.AllTeachActionDiffItemlOAD();
    }
}

void QTrainMainWindow::DiffSoundLoadInit(QByteArray &Data)
{

    downLoadSoundFile(Data);
    if(m_DiffsoundInfo[0].isEmpty())
    {
        m_DiffsoundInfo[0]=Data;
        return;
    }
    if( m_DiffsoundInfo[1].isEmpty())
    {
        m_DiffsoundInfo[1]=Data;
        return;
    }
}

void QTrainMainWindow::CompareItem1(diffSound &data)
{
    m_DiffsoundInfo[0].clear();
    baseTree.restoreTreeItemWidget(data);
    if(Synchronous)
    {
         QString index=QString("0")+QString(":")+QString("%1").arg(data.m_strId);
        m_manager.AllTeachActionDiffItemDelete(index);
    }
}
void QTrainMainWindow::CompareItem2(diffSound &data)
{
    m_DiffsoundInfo[1].clear();
    baseTree.restoreTreeItemWidget(data);
    if(Synchronous)
    {
        QString index=QString("1")+QString(":")+QString("%1").arg(data.m_strId);
        m_manager.AllTeachActionDiffItemDelete(index);
    }
}
void QTrainMainWindow::downLoadSoundFile(QByteArray &Data)
{
    QJsonDocument jDoc;
    QJsonParseError jsonError;
    jDoc = QJsonDocument::fromJson(Data,&jsonError);
    if(jsonError.error == QJsonParseError::NoError)
    {
        if (jDoc.isObject())
        {
             QJsonObject rootObj = jDoc.object();
             if(rootObj.value("system_custom").toString()==QString("1"))
             {
                 QString downloadFile=rootObj.value("sound_file").toString();
                 QFileInfo info(downloadFile);
                 webmanager.downloadfile(downloadFile,QCoreApplication::applicationDirPath()+QString("/Resource/Sounds/UserSound/")+info.fileName());
//                 if(TipBox->isHidden())
//                 {
//                     TipBox->setText(QStringLiteral("正在更新音源信息"));
//                     TipBox->exec();
//                 }
             }
        }
    }
}

void QTrainMainWindow::GetDiffData()
{
    webmanager.GetDiffSound();
}
void QTrainMainWindow::GetCustomWare()
{
     webmanager.GetCustomCourse();
}
void QTrainMainWindow::doRequest(int deskID, int State)
{
    Q_UNUSED(deskID);
    if(State==REQUEST)
    {
        this->talk_btn->setStyleSheet(" image:url(:/images/talk_Btn_Request.png);");
        if(talkwindow->popup)
        {
           talkwindow->exec();
        }
    }
    else
    {
        return;
    }
}

void QTrainMainWindow::doChangTalkBntIcon()
{
    talk_btn->setStyleSheet("image:url(:/images/intercom_button.png);");
}

//串口初始化
void QTrainMainWindow::InitComm()
{
    m_pSerialPort = new QSerialPort(this);
    QSettings *readconfig=new QSettings(APPPATH,QSettings::IniFormat);
    QString ComPort=readconfig->value("System_Param/Comm").toString();
    delete readconfig;
    m_pSerialPort->setPortName(ComPort);
    if(m_pSerialPort->open(QIODevice::ReadWrite))
    {
        m_pSerialPort->setBaudRate(2400);
        m_pSerialPort->setParity(QSerialPort::NoParity);
        m_pSerialPort->setDataBits(QSerialPort::Data8);
        m_pSerialPort->setStopBits(QSerialPort::OneStop);
        m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        m_pSerialPort->clear();
        m_pSerialPort->clearError();
    }
    else
    {
        qDebug()<<__FUNCTION__<<m_pSerialPort->errorString();
    }
    connect(m_pSerialPort,SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
}


/****************主界面事件函数********************/
void QTrainMainWindow::mousePressEvent (QMouseEvent *event)
{

   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}

void QTrainMainWindow::mouseMoveEvent(QMouseEvent * event)
{
  // 这个if 判断只是为了保证是按压鼠标左键移动产生窗体拖动效果 以及是否在topLabel
  if (event->buttons() == Qt::LeftButton&&this->top_label->frameRect().contains(this->xOffset,this->yOffset))
  {
     this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
  }
}

void QTrainMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

void QTrainMainWindow::timerEvent(QTimerEvent *event)
{
    if(m_nDelayHandle == event->timerId())
    {
        killTimer(m_nDelayHandle);

        QComOrder comOrder;
        QByteArray data;

        if(m_nState != 3)
        {
//           qDebug()<<__FUNCTION__<<"playing";
            //下发扩音听诊模式
            comOrder.GetTeachModeOrder(2,data);
            m_pSerialPort->write(data);
            m_nState = 3;
            //
            m_pSoundControl->OnLoudAuscultateHandle();
        }
        else
        {
//            qDebug()<<__FUNCTION__<<"stoping";
            //下发教学讲解模式
            comOrder.GetTeachModeOrder(0,data);
            m_pSerialPort->write(data);
            m_nState = 0;
            m_pSoundControl->OnStopLoudAuscultate();
        }

        //发送停止震颤命令
        comOrder.GetStopVidrOrder(data);
        m_pSerialPort->write(data);

        m_nDelayHandle = 0;
    }
}
