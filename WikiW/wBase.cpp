/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wBase.cpp
*
* WikiW is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WikiW is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "stdafx.h"
#include "wApp.h"
#include "wBase.h"

IMPLEMENT_DYNAMIC ( CWikiBase, CFrameWnd )

BEGIN_MESSAGE_MAP ( CWikiBase, CFrameWnd )
	ON_WM_PAINT ( )
	ON_WM_ERASEBKGND ( )
	ON_WM_NCHITTEST ( )
	ON_WM_SIZE ( )
	ON_WM_WINDOWPOSCHANGING ( )
	ON_NOTIFY ( TCN_SELCHANGE, IDC_CMAINTAB, OnSelchangeTab )
	ON_NOTIFY ( TCN_SELCHANGING, IDC_CMAINTAB, OnSelchangingTab )
	ON_BN_CLICKED ( IDC_B_HIDEAPP, OnBHideAppClick )
	ON_BN_CLICKED ( IDC_B_CLOSEAPP, OnBCloseAppClick )
END_MESSAGE_MAP ( )

CWikiBase::CWikiBase ( )
{
	m_hIcon = AfxGetApp ( )->LoadIcon ( IDI_MAINICON );
}

CWikiBase::~CWikiBase ( )
{
}

void CWikiBase::OnSelchangingTab ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//CString xRGBColor; xRGBColor.Format ( _T ( "%d, %d, %d" ), m_TabCtrl.GetCurSel ( ), m_TabCtrl.GetCurFocus ( ), ActiveTabID );
	//SetWindowText ( xGetTime() + L"|" + xRGBColor );
}

void CWikiBase::OnSelchangeTab ( NMHDR* pNMHDR, LRESULT* pResult )
{
	if ( ActiveTabID != m_TabCtrl.GetCurSel ( ) )
		if ( CWnd *m_pInfo = ( CWnd* ) m_pPages[ m_TabCtrl.GetCurSel ( ) ] )
		{
			m_pActiveTab->ShowWindow ( SW_HIDE );
			m_pActiveTab = m_pInfo;
			m_pActiveTab->ShowWindow ( SW_SHOW );
			m_TabCtrl.UpdateWindow ( );
			m_pActiveTab->UpdateWindow ( );
			ActiveTabID = m_TabCtrl.GetCurSel ( );
		}
	*pResult = 0;
}

void CWikiBase::OnPaint ( void )
{
	SetIcon ( m_hIcon, TRUE );
	SetIcon ( m_hIcon, FALSE );

	return afx_msg void ( );
}

BOOL CWikiBase::OnEraseBkgnd ( CDC* pDC )
{
	CBrush backBrush ( so.SKIN_COLOR_APP_BG );
	CBrush* pOldBrush = pDC->SelectObject ( &backBrush );
	CRect rect;
	pDC->GetClipBox ( &rect );
	pDC->PatBlt ( rect.left, rect.top, rect.Width ( ), rect.Height ( ), PATCOPY );
	pDC->SelectObject ( pOldBrush );
	pDC->FrameRect ( rect, &so.SKIN_COLOR_APP_BORDER );

	return TRUE;
}

LRESULT CWikiBase::OnNcHitTest ( CPoint point ) // move window
{
	UINT ret = ( UINT ) CFrameWnd::OnNcHitTest ( point );
	if ( ret == HTCLIENT )
		return HTCAPTION;
	return ret;
}

void CWikiBase::OnWindowPosChanging ( WINDOWPOS* lpwndpos )
{
	CFrameWnd::OnWindowPosChanging ( lpwndpos );
	if ( !isWindowMinimized )
	{
		CRect rcMonitor;
		this->GetWindowRect ( &rcMonitor );

		theApp.WindowTop = rcMonitor.top;
		theApp.WindowLeft = rcMonitor.left;

		theApp.app_title.Format ( _T ( "%d, %d" ), theApp.WindowTop, theApp.WindowLeft );
		SetWindowText ( theApp.app_title );
	}
}

BOOL CWikiBase::PreCreateWindow ( CREATESTRUCT& cs )
{
	if ( !CFrameWnd::PreCreateWindow ( cs ) )
		return FALSE;
	/*
	cs.style = WS_EX_CLIENTEDGE | WS_MINIMIZEBOX | WS_SYSMENU;
	//cs.dwExStyle &= ~( WS_EX_CLIENTEDGE | WS_MAXIMIZEBOX );
	cs.dwExStyle &= WS_OVERLAPPED;// | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU;
	//cs.dwExStyle &= ~( WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU );
	*/
	cs.dwExStyle &= ~( WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU );
	return TRUE;
}

void CWikiBase::OnSize ( UINT nType, int cx, int cy )
{
	switch ( nType )
	{
	case SIZE_MAXIMIZED:
		// window was maximized
		break;
	case SIZE_MINIMIZED:
		// window was minimized
		break;
	case SIZE_RESTORED:
		UpdateWindow ( );
		isWindowMinimized = false;
		break;
	default:
		// 
		break;
	}
}

void CWikiBase::OnBHideAppClick ( void )
{
	ShowWindow ( SW_MINIMIZE );
	isWindowMinimized = true;
	return afx_msg void ( );
}

void CWikiBase::OnBCloseAppClick ( void )
{
	BOOL rc = DestroyWindow ( );
	if ( !rc )
	{
		TRACE0 ( "\n Ошибка 7. Окно не было разрушено \n" );
		exit ( 7 );
	}
	return afx_msg void ( );
}

void CWikiBase::CreateChildControls ( void )
{
	SetWindowText ( theApp.app_title );

	xCreateFastFont ( f_blM_Main, 26, 600, _T ( "Tahoma" ) );

	b_CloseApp.Create ( L"X", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth - 30, 1, theApp.WindowWidth - 1, 30 ), this, IDC_B_CLOSEAPP );
	b_HideApp.Create ( L"_", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth - 60, 1, theApp.WindowWidth - 30, 30 ), this, IDC_B_HIDEAPP );
	b_Title.Create ( theApp.app_title, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 0, 1, theApp.WindowWidth - 60, 30 ), this, IDC_B_TITLEAPP );
	b_Title.Draggable = true;


	b_lM_Opener.Create ( L"《", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 0, 30, 30, 349 ), this, IDC_B_LEFT_OPENER );
	//b_lM_Main.Create ( L"WikiW", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 200, 40 ), this, IDC_B_TITLE );
	//b_lM_User.Create ( L"WikiW", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 200, 40 ), this, IDC_B_TITLE );
	b_lM_Opener.SetFont ( &f_blM_Main );

	/*
	b_Options.Create ( L"Настройки", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 220, 10, 350, 40 ), this, IDC_B_OPTIONS );
	b_Title.Create ( theApp.app_title, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 200, 40 ), this, IDC_B_TITLE );
	b_Options.SetFont ( &f_TitleButBig );
	b_Title.SetFont ( &f_TitleButBig );
	b_Title.Draggable = true;

	m_TabCtrl.Create ( TCS_TABS | TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE,
					   CRect ( 10, 50, 575, 350 ), this, IDC_CMAINTAB );

	m_pPages.push_back ( new CWikiBasePage1 );
	TCITEM tcItem1;
	tcItem1.mask = TCIF_TEXT;
	tcItem1.pszText = _T ( "Tab #1" );
	m_TabCtrl.InsertItem ( 0, &tcItem1 );
	m_pPages[ 0 ]->Create ( NULL, NULL, NULL, CRect ( 20, 85, 365, 340 ), this, NULL, NULL );
	(( CWikiBasePage1 *) m_pPages[ 0 ])->CreateChildControls ( );
	m_pPages[ 0 ]->UpdateWindow ( );
	m_pPages[ 0 ]->ShowWindow ( SW_HIDE );

	m_pPages.push_back ( new CWikiBasePage2 );
	TCITEM tcItem2;
	tcItem2.mask = TCIF_TEXT;
	tcItem2.pszText = _T ( "Tab #2" );
	m_TabCtrl.InsertItem ( 1, &tcItem2 );
	m_pPages[ 1 ]->Create ( NULL, NULL, NULL, CRect ( 100, 85, 565, 340 ), this, NULL, NULL );
	( ( CWikiBasePage2 * ) m_pPages[ 1 ] )->CreateChildControls ( );
	m_pPages[ 1 ]->UpdateWindow ( );
	m_pPages[ 1 ]->ShowWindow ( SW_HIDE );

	m_pActiveTab = m_pPages[ 0 ];
	ActiveTabID = 0;

	m_TabCtrl.SetFont ( &f_TitleButBig );

	m_TabCtrl.ShowWindow ( SW_HIDE );
	*/
}


CWikiBasePage1::CWikiBasePage1 ( )
{
}
CWikiBasePage1::~CWikiBasePage1 ( )
{
}
BOOL CWikiBasePage1::PreCreateWindow ( CREATESTRUCT& cs )
{
	if ( !CWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass ( CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor ( NULL, IDC_ARROW ), reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 ), NULL );
	return TRUE;
}
void CWikiBasePage1::CreateChildControls ( void )
{
	SetWindowText ( theApp.app_title );

	xCreateFastFont ( f_TitleButBig, 20, 600, _T ( "Jura" ) );

	b_Options.Create ( L"Настройки", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 250, 130 ), this, IDC_BBBAT3 );
	b_Options.SetFont ( &f_TitleButBig );
}

CWikiBasePage2::CWikiBasePage2 ( )
{
}
CWikiBasePage2::~CWikiBasePage2 ( )
{
}
BOOL CWikiBasePage2::PreCreateWindow ( CREATESTRUCT& cs )
{
	if ( !CWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass ( CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor ( NULL, IDC_ARROW ), reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 ), NULL );
	return TRUE;
}
void CWikiBasePage2::CreateChildControls ( void )
{
	SetWindowText ( theApp.app_title );

	xCreateFastFont ( f_TitleButBig, 20, 600, _T ( "Jura" ) );

	b_Options.Create ( L"Настройки", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 260, 10, 550, 130 ), this, IDC_BBBAT4 );
	b_Options.SetFont ( &f_TitleButBig );
}
