#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T14:20:52
#
#-------------------------------------------------

QT       += core gui network multimedia serialport axcontainer sql webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhysicalCheckTrainTeacher
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        qtrainmainwindow.cpp \
    auscultation_widget.cpp \
    case_widget.cpp \
    courseware_widget.cpp \
    main_tab.cpp \
    talkbackview.cpp \
    loginbackgroundform.cpp \
    loginform.cpp \
    qchosecurriculumview.cpp \
    qcompareview.cpp \
    listen.cpp \
    speak.cpp \
    qtouchtrainview.cpp \
    qsetsystemview.cpp \
    setitemview.cpp \
    qmanager.cpp \
    net_server.cpp \
    tellclientconnected.cpp \
    m_ftp_manager.cpp \
    qdatabase.cpp \
    qcomorder.cpp \
    qgettreecontentfromweb.cpp \
    qloudauscultatecontrolvir.cpp \
    qloudauscultategeneralcontrol.cpp \
    qloudauscultatetouchcontrol.cpp \
    qloudauscultatetouchplayparts.cpp \
    qparseinfofromweb.cpp \
    qsoundcontrol.cpp \
    qsoundplayparts.cpp \
    qsoundresource.cpp \
    aboutform.cpp \
    myswitchbutton.cpp \
    qflashtree.cpp \
    qcoursewareinfo.cpp \
    qparsecoursewarefileop.cpp \
    qparsecousewarefile.cpp \
    qcsorder.cpp

HEADERS  += qtrainmainwindow.h \
    auscultation_widget.h \
    case_widget.h \
    courseware_widget.h \
    define.h \
    main_tab.h \
    talkbackview.h \
    loginbackgroundform.h \
    loginform.h \
    qchosecurriculumview.h \
    qcompareview.h \
    listen.h \
    speak.h \
    qtouchtrainview.h \
    qsetsystemview.h \
    setitemview.h \
    qmanager.h \
    net_server.h \
    tellclientconnected.h \
    m_ftp_manager.h \
    qdatabase.h \
    globalcommon.h \
    HLDocWavFile.h \
    HLEncryptWaveFile.h \
    HLFileWavStreamIn.h \
    HLLoopBuff.h \
    HLVirSoundBuff.h \
    HLWavFile.h \
    HLWavStreamOut.h \
    PlayWavDll.h \
    qcomorder.h \
    qgettreecontentfromweb.h \
    qloudauscultatecontrolvir.h \
    qloudauscultategeneralcontrol.h \
    qloudauscultatetouchcontrol.h \
    qloudauscultatetouchplayparts.h \
    qparseinfofromweb.h \
    qsoundcontrol.h \
    qsoundplayparts.h \
    qsoundresource.h \
    aboutform.h \
    myswitchbutton.h \
    qflashtree.h \
    qcoursewareinfo.h \
    qparsecoursewarefileop.h \
    qparsecousewarefile.h \
    qcsorder.h

FORMS    += qtrainmainwindow.ui \
    auscultation_widget.ui \
    case_widget.ui \
    courseware_widget.ui \
    talkbackview.ui \
    loginform.ui \
    qcompareview.ui \
    qsetsystemview.ui \
    setitemview.ui \
    aboutform.ui

RESOURCES += \
    resource.qrc
INCLUDEPATH += $$PWD/include

LIBS+=$$PWD/lib/va_g729a.lib
LIBS += legacy_stdio_definitions.lib
LIBS    += -L$$PWD/Lib/ -lMFCdll
