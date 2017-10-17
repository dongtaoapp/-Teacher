#include "qmaxwidget.h"
#include "Windows.h"
#include "define.h"
WNDPROC preWndProc;//��Ϊȫ�ֱ�������
LONG VILPSSwfProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
  if(msg==WM_RBUTTONDOWN)//��������Ҽ�
     return 0;
  return CallWindowProc((WNDPROC)preWndProc,hwnd,msg,wParam,lParam);//����ԭ���Ĵ��ڹ���
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
     HWND sx=GetTopWindow((HWND)hwnd);//��õ�һ���Ӵ���
     sx=GetTopWindow(sx);//��õ�һ���Ӵ���
     if (sx>0)
    {
        preWndProc=(WNDPROC)::SetWindowLong(sx,GWL_WNDPROC,(LONG)VILPSSwfProc);//�������ô��ڹ���
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
