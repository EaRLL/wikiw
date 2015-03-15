#include "stdafx.h"
#include "wApp.h"
#include "wBase.h"

IMPLEMENT_DYNAMIC ( CWikiBase, CFrameWnd )

BEGIN_MESSAGE_MAP ( CWikiBase, CFrameWnd )
	ON_WM_PAINT ( )
END_MESSAGE_MAP()

CWikiBase::CWikiBase ( )
{
	m_hIcon = AfxGetApp ( )->LoadIcon ( IDI_MAINICON );
}

CWikiBase::~CWikiBase ( )
{
}

void CWikiBase::OnPaint ( void )
{
	SetIcon ( m_hIcon, TRUE );
	SetIcon ( m_hIcon, FALSE );

	return afx_msg void ( );
}


BOOL CWikiBase::PreCreateWindow ( CREATESTRUCT& cs )
{
	if ( !CFrameWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.style = WS_EX_CLIENTEDGE | /*WS_THICKFRAME |*/ WS_MINIMIZEBOX | WS_SYSMENU;
	//cs.dwExStyle &= ~( WS_EX_CLIENTEDGE | WS_MAXIMIZEBOX );
	//cs.dwExStyle &= WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
}
