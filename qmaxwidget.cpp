#include "qmaxwidget.h"
#include "Windows.h"
#include "define.h"
WNDPROC preWndProc;//设为全局变量即可
LONG VILPSSwfProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  if(msg==WM_RBUTTONDOWN)//屏蔽鼠标右键
     return 0;
  return CallWindowProc((WNDPROC)preWndProc,hwnd,msg,wParam,lParam);//调用原来的窗口过程
}
QMAxWidget::QMAxWidget(QWidget *parent):
    QAxWidget(parent)
{
       this->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
        Init();
}

void QMAxWidget::loadFlash(QString &path)
{
    this->dynamicCall("LoadMovie(long,string)",0,path);

}

void QMAxWidget::Init()
{
    WId hwnd=this->winId();
    if (hwnd>0)
    {
     HWND sx=GetTopWindow((HWND)hwnd);//获得第一个子窗口
     sx=GetTopWindow(sx);//获得第一个子窗口
     if (sx>0)
    {
        preWndProc=(WNDPROC)::SetWindowLong(sx,GWL_WNDPROC,(LONG)VILPSSwfProc);//重新设置窗口过程
     }
    }
}


void QMAxWidget::PausePlay()
{
    this->dynamicCall("CallFunction(string)",FLASHPAUSE);
}
void QMAxWidget::StartPlay()
{
    this->dynamicCall("CallFunction(string)",FLASHPLAY);
}
