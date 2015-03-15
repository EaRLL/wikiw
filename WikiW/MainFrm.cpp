#include "stdafx.h"
#include "WikiW.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//ON_WM_CREATE()
	//ON_WM_SETFOCUS()
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

/*int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	return 0;
}*/

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	/*if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);*/

	if ( !CFrameWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.style = WS_EX_CLIENTEDGE | /*WS_THICKFRAME |*/ WS_MINIMIZEBOX | WS_SYSMENU;
	//cs.dwExStyle &= ~( WS_EX_CLIENTEDGE | WS_MAXIMIZEBOX );
	//cs.dwExStyle &= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

/*void CMainFrame::OnSetFocus(CWnd* )
{
	m_wndView.SetFocus();
}*/

/*BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
*/