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
* along with WikiW.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "stdafx.h"
#include "wApp.h"
#include "wBase.h"
#include "CWikiBasePage1.h"
#include "CWikiBasePage2.h"

IMPLEMENT_DYNAMIC ( CWikiBase, CFrameWnd )

BEGIN_MESSAGE_MAP ( CWikiBase, CFrameWnd )
	ON_WM_PAINT ( )
	ON_WM_ERASEBKGND ( )
	ON_WM_NCHITTEST ( )
	ON_WM_SIZE ( )
	ON_WM_WINDOWPOSCHANGING ( )
	ON_BN_CLICKED ( IDC_B_HIDEAPP, OnBHideAppClick )
	ON_BN_CLICKED ( IDC_B_CLOSEAPP, OnBCloseAppClick )
	ON_CONTROL_RANGE ( BN_CLICKED, IDC_B_LEFT_OPENER, IDC_B_LEFT_MENU_USER, OnBLMenuButtonClick )
END_MESSAGE_MAP ( )

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

BOOL CWikiBase::OnEraseBkgnd ( CDC* pDC )
{
	CBrush backBrush ( so.APP_COLOR_BG );
	CBrush* pOldBrush = pDC->SelectObject ( &backBrush );
	CRect rect;
	pDC->GetClipBox ( &rect );
	pDC->PatBlt ( rect.left, rect.top, rect.Width ( ), rect.Height ( ), PATCOPY );
	pDC->SelectObject ( pOldBrush );
	pDC->FrameRect ( rect, &so.APP_COLOR_BORDER );

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

		//theApp.app_title.Format ( _T ( "%d, %d" ), theApp.WindowTop, theApp.WindowLeft );
		//SetWindowText ( theApp.app_title );
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
}

void CWikiBase::OnBCloseAppClick ( void )
{
	BOOL rc = DestroyWindow ( );
	if ( !rc )
	{
		TRACE0 ( "\n Ошибка 7. Окно не было разрушено \n" );
		exit ( 7 );
	}
}

void CWikiBase::ShowLeftMenu ( )
{
	if ( isLeftMenuVisible )
	{
		theApp.WindowWidth = theApp.WindowWidth - 200;
		this->SetWindowPos ( NULL, theApp.WindowLeft, theApp.WindowTop, theApp.WindowWidth, theApp.WindowHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );

		isLeftMenuVisible = false;
		b_lM_Opener.SetWindowText ( L"»" );

		b_CloseApp.MoveWindow ( CRect ( theApp.WindowWidth - 30, 1, theApp.WindowWidth - 1, 30 ) );
		b_HideApp.MoveWindow ( CRect ( theApp.WindowWidth - 60, 1, theApp.WindowWidth - 30, 30 ) );
		b_Title.MoveWindow ( CRect ( 1, 1, theApp.WindowWidth - 60, 30 ) );
		UpdateWindow ( );
	}
	else
	{
		theApp.WindowWidth = theApp.WindowWidth + 200;
		this->SetWindowPos ( NULL, theApp.WindowLeft, theApp.WindowTop, theApp.WindowWidth, theApp.WindowHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );

		isLeftMenuVisible = true;
		b_lM_Opener.SetWindowText ( L"«" );

		b_CloseApp.MoveWindow ( CRect ( theApp.WindowWidth - 30, 1, theApp.WindowWidth - 1, 30 ) );
		b_HideApp.MoveWindow ( CRect ( theApp.WindowWidth - 60, 1, theApp.WindowWidth - 30, 30 ) );
		b_Title.MoveWindow ( CRect ( 1, 1, theApp.WindowWidth - 60, 30 ) );
		UpdateWindow ( );

	}
}

void CWikiBase::OnBLMenuButtonClick ( UINT uiID )
{
	if ( uiID == IDC_B_LEFT_MENU_MAIN || uiID == IDC_B_LEFT_MENU_USER )
		LeftMenuClear ( );

	switch ( uiID )
	{
	case IDC_B_LEFT_MENU_MAIN:
		isLeftMenuMain = true;
		if ( ActiveTabID != 0 )
		{
			m_pPages[ ActiveTabID ]->ShowWindow ( SW_HIDE );
			m_pPages[ 0 ]->ShowWindow ( SW_SHOW );
			m_pPages[ 0 ]->UpdateWindow ( );
			ActiveTabID = 0;
		}
		break;
	case IDC_B_LEFT_MENU_USER:
		isLeftMenuUser = true;
		if ( ActiveTabID != 1 )
		{
			m_pPages[ ActiveTabID ]->ShowWindow ( SW_HIDE );
			m_pPages[ 1 ]->ShowWindow ( SW_SHOW );
			m_pPages[ 1 ]->UpdateWindow ( );
			ActiveTabID = 1;
		}
		break;
	case IDC_B_LEFT_OPENER:
		ShowLeftMenu ( );
		break;
	}

	if ( uiID == IDC_B_LEFT_MENU_MAIN || uiID == IDC_B_LEFT_MENU_USER )
		LeftMenuSelectOpt ( );
}

void CWikiBase::CreateChildControls ( void )
{
	SetWindowText ( theApp.app_title );

	xCreateFastFont ( f_blM_Opener, 26, 600, _T ( "Tahoma" ) );
	xCreateFastFont ( f_blM_Std, 16, 400, _T ( "Tahoma" ) );
	xCreateFastFont ( f_bTopMenu, 16, 400, _T ( "Tahoma" ) );

	b_CloseApp.Create ( L"X", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth - 30, 1, theApp.WindowWidth - 1, 30 ), this, IDC_B_CLOSEAPP );
	b_HideApp.Create ( L"_", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth - 60, 1, theApp.WindowWidth - 30, 30 ), this, IDC_B_HIDEAPP );
	b_Title.Create ( theApp.app_title, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 1, 1, theApp.WindowWidth - 60, 30 ), this, IDC_B_TITLEAPP );

	b_lM_Opener.Create ( L"»", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth - 50, 30, theApp.WindowWidth - 10, 349 ), this, IDC_B_LEFT_OPENER );

	b_lM_Main.Create ( L"Главная", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth, 40, theApp.WindowWidth + 199, 80 ), this, IDC_B_LEFT_MENU_MAIN );
	b_lM_User.Create ( L"Участник", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( theApp.WindowWidth, 90, theApp.WindowWidth + 199, 130 ), this, IDC_B_LEFT_MENU_USER );

	b_CloseApp.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_HideApp.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_Title.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_lM_Opener.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBGrayColors );
	b_lM_Main.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_lM_User.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBGrayColors );

	b_CloseApp.SetFont ( &f_bTopMenu );
	b_HideApp.SetFont ( &f_bTopMenu );
	b_Title.SetFont ( &f_bTopMenu );
	b_lM_Opener.SetFont ( &f_blM_Opener );
	b_lM_Main.SetFont ( &f_blM_Std );
	b_lM_User.SetFont ( &f_blM_Std );

	b_Title.Draggable = true;


	m_pPages.push_back ( new CWikiBasePage1 );
	m_pPages[ 0 ]->Create ( NULL, NULL, NULL, CRect ( 10, 40, 540, 340 ), this, NULL, NULL );
	( ( CWikiBasePage1 * ) m_pPages[ 0 ] )->CreateChildControls ( );
	m_pPages[ 0 ]->UpdateWindow ( );
	m_pPages[ 0 ]->ShowWindow ( SW_SHOW );

	m_pPages.push_back ( new CWikiBasePage2 );
	m_pPages[ 1 ]->Create ( NULL, NULL, NULL, CRect ( 10, 40, 540, 340 ), this, NULL, NULL );
	( ( CWikiBasePage2 * ) m_pPages[ 1 ] )->CreateChildControls ( );
	m_pPages[ 1 ]->UpdateWindow ( );
	m_pPages[ 1 ]->ShowWindow ( SW_HIDE );

	ActiveTabID = 0;
}

void CWikiBase::LeftMenuClear ( )
{
	isLeftMenuMain = false;
	isLeftMenuUser = false;
}

void CWikiBase::LeftMenuSelectOpt ( )
{
	if ( isLeftMenuMain )
		b_lM_Main.b_Colors = reinterpret_cast< CFlatButton::sColors* >( &so.FlatBMainColors );
	else
		b_lM_Main.b_Colors = reinterpret_cast< CFlatButton::sColors* >( &so.FlatBGrayColors );

	if ( isLeftMenuUser )
		b_lM_User.b_Colors = reinterpret_cast< CFlatButton::sColors* >( &so.FlatBMainColors );
	else
		b_lM_User.b_Colors = reinterpret_cast< CFlatButton::sColors* >( &so.FlatBGrayColors );

	b_lM_Main.RedrawWindow ( );
	b_lM_User.RedrawWindow ( );
}
