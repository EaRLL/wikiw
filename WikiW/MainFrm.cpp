#include "stdafx.h"
#include "WikiW.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP ( CMainFrame, CFrameWnd )
	ON_WM_PAINT ( )
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
	m_hIcon = AfxGetApp ( )->LoadIcon ( IDI_MAINICON );
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnPaint ( void )
{
	SetIcon ( m_hIcon, TRUE );
	SetIcon ( m_hIcon, FALSE );

	return afx_msg void ( );
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if ( !CFrameWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.style = WS_EX_CLIENTEDGE | /*WS_THICKFRAME |*/ WS_MINIMIZEBOX | WS_SYSMENU;
	//cs.dwExStyle &= ~( WS_EX_CLIENTEDGE | WS_MAXIMIZEBOX );
	//cs.dwExStyle &= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
}
