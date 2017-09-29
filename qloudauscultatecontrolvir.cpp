#include "qloudauscultatecontrolvir.h"

QLoudAuscultateControlVir::QLoudAuscultateControlVir(HWND hWnd, QString strAppPath)
{
    m_strAppPath = strAppPath;
    m_bEnableLoudAuscultate = FALSE;
    m_bLoudAuscultating = FALSE;
}

QLoudAuscultateControlVir::~QLoudAuscultateControlVir()
{

}
