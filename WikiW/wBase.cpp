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
	ON_NOTIFY ( TCN_SELCHANGE, IDC_CMAINTAB, OnSelchangeTab )
	//ON_NOTIFY ( TCN_SELCHANGING, IDC_CMAINTAB, OnSelchangingTab )
END_MESSAGE_MAP()

/*void CWikiBase::OnSelchangingTab ( NMHDR* pNMHDR, LRESULT* pResult )
{
	if ( m_TabCtrl.GetCurSel ( ) != m_TabCtrl.GetCurFocus ( ) && ActiveTabID != m_TabCtrl.GetCurSel ( ) )
	{
		CString xRGBColor; xRGBColor.Format ( _T ( "%d, %d, %d" ), m_TabCtrl.GetCurSel ( ), m_TabCtrl.GetCurFocus ( ), ActiveTabID );
		SetWindowText ( xRGBColor );
		m_pActiveTab->ShowWindow ( SW_HIDE );
	}
	
	TCITEM tci;
	tci.mask = TCIF_PARAM;
	m_TabCtrl->GetItem ( m_TabCtrl->GetCurFocus ( ), &tci );
	
	if ( CWnd *m_pInfo = ( CWnd* ) tci.lParam )
	{
		m_pInfo->ShowWindow ( SW_HIDE );
		//m_pInfo->UpdateWindow ( );
	}
	//*pResult = 0;
	
}*/

void CWikiBase::OnSelchangeTab ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//TCITEM tci;
	//tci.mask = TCIF_PARAM;
	//m_TabCtrl->GetItem ( m_TabCtrl->GetCurSel ( ), &tci );
	//		CString xRGBColor; xRGBColor.Format ( _T ( "%d, %d, %d" ), m_TabCtrl.GetCurSel ( ), m_TabCtrl.GetCurFocus ( ), ActiveTabID );
	//		SetWindowText ( xRGBColor );
	if ( ActiveTabID != m_TabCtrl.GetCurSel ( ) )
		if ( CWnd *m_pInfo = ( CWnd* ) m_pPages[ m_TabCtrl.GetCurSel ( ) ] )
		{
			//m_pActiveTab->ShowWindow ( SW_HIDE );
			m_pPages[ ActiveTabID ]->ShowWindow ( SW_HIDE );
			m_pInfo->ShowWindow ( SW_SHOW );
			m_pInfo->UpdateWindow ( );
			m_pActiveTab = NULL;
			m_pActiveTab = m_pInfo;
			ActiveTabID = m_TabCtrl.GetCurSel ( );
		}
	//*pResult = 0;
}

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

void CWikiBase::CreateChildControls ( void )
{
	SetWindowText ( theApp.app_title );

	xCreateFastFont ( f_TitleButBig, 20, 600, _T ( "Jura" ) );

	b_Options.Create ( L"Настройки", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 220, 10, 350, 40 ), this, IDC_B_OPTIONS );
	b_Title.Create ( theApp.app_title, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 200, 40 ), this, IDC_B_TITLE );
	b_Options.SetFont ( &f_TitleButBig );
	b_Title.SetFont ( &f_TitleButBig );
	b_Title.Draggable = true;

	//CTabCtrl* m_TabCtrl = new CTabCtrl;

	m_TabCtrl.Create ( TCS_TABS | TCS_FIXEDWIDTH | WS_CHILD | WS_VISIBLE,
					   CRect ( 10, 50, 575, 350 ), this, IDC_CMAINTAB );

	/*TCITEM tcItem;

	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T ( "Tab #1" );
	m_TabCtrl->InsertItem ( 0, &tcItem );

	tcItem.mask = TCIF_TEXT;
	tcItem.pszText = _T ( "Tab #2" );
	m_TabCtrl->InsertItem ( 1, &tcItem );

	m_TabCtrl->SetFont ( &f_TitleButBig );

	CWikiBasePage1* pPage1 = new CWikiBasePage1;
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = ( LPARAM ) pPage1;
	m_TabCtrl->SetItem ( 0, &tcItem );
	pPage1->Create ( NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect ( 20, 85, 565, 340 ), this, NULL, NULL );
	pPage1->ShowWindow ( SW_SHOW );
	pPage1->CreateChildControls ( );
	pPage1->UpdateWindow ( );

	CWikiBasePage2* pPage2 = new CWikiBasePage2;
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = ( LPARAM ) pPage2;
	m_TabCtrl->SetItem ( 1, &tcItem );
	pPage2->Create ( NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect ( 20, 85, 565, 340 ), this, NULL, NULL );
	pPage2->ShowWindow ( SW_HIDE );
	pPage2->CreateChildControls ( );
	pPage2->UpdateWindow ( );*/



	//CWikiBasePage1* pPage1 = new CWikiBasePage1;
	m_pPages.push_back ( new CWikiBasePage1 );
	TCITEM tcItem1;
	tcItem1.mask = TCIF_TEXT;
	tcItem1.pszText = _T ( "Tab #1" );
	m_TabCtrl.InsertItem ( 0, &tcItem1 );
	m_pPages[ 0 ]->Create ( NULL, NULL, NULL, CRect ( 20, 85, 365, 340 ), this, NULL, NULL );
	(( CWikiBasePage1 *) m_pPages[ 0 ])->CreateChildControls ( );
	m_pPages[ 0 ]->UpdateWindow ( );
	m_pPages[ 0 ]->ShowWindow ( SW_SHOW );
	//TCITEM ptcItem1;
	//ptcItem1.mask = TCIF_PARAM;
	//ptcItem1.lParam = ( LPARAM ) pPage1;
	//m_TabCtrl->SetItem ( 0, &ptcItem1 );

	//CWikiBasePage2* pPage2 = new CWikiBasePage2;
	m_pPages.push_back ( new CWikiBasePage2 );
	TCITEM tcItem2;
	tcItem2.mask = TCIF_TEXT;
	tcItem2.pszText = _T ( "Tab #2" );
	m_TabCtrl.InsertItem ( 1, &tcItem2 );
	m_pPages[ 1 ]->Create ( NULL, NULL, NULL, CRect ( 100, 85, 565, 340 ), this, NULL, NULL );
	( ( CWikiBasePage2 * ) m_pPages[ 1 ] )->CreateChildControls ( );
	m_pPages[ 1 ]->UpdateWindow ( );
	m_pPages[ 1 ]->ShowWindow ( SW_HIDE );
	//TCITEM ptcItem2;
	//ptcItem2.mask = TCIF_PARAM;
	//ptcItem2.lParam = ( LPARAM ) pPage2;
	//m_TabCtrl->SetItem ( 1, &ptcItem2 );

	m_pActiveTab = m_pPages[ 0 ];
	ActiveTabID = 0;

	m_TabCtrl.SetFont ( &f_TitleButBig );

	/*BOOL rc = pPage1->Create ( NULL, L"text", WS_OVERLAPPEDWINDOW, CRect ( 0, 0, 0, 0 ), this, NULL, NULL );
	if ( !rc )
	{
		TRACE0 ( "\n Ошибка 1\n" );
		exit ( 1 );
	}
	pPage1->SetWindowPos ( NULL, 20, 60, 500, 300, SWP_NOSIZE | SWP_NOZORDER );
	pPage1->CreateChildControls ( );
	pPage1->ShowWindow ( SW_SHOW );
	pPage1->UpdateWindow ( );*/

	/*CWikiBasePage1* pPage1;
	pPage1 = new CWikiBasePage1;
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = ( LPARAM ) pPage1;
	m_TabCtrl->SetItem ( 0, &tcItem );
	//VERIFY ( pPage1->Create ( CWikiBasePage1, &m_TabCtrl ) );
	pPage1->SetWindowPos ( NULL, 10, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	pPage1->ShowWindow ( SW_SHOW );

	CWikiBasePage2* pPage2;
	pPage2 = new CWikiBasePage2;
	tcItem.mask = TCIF_PARAM;
	tcItem.lParam = ( LPARAM ) pPage2;
	m_TabCtrl->SetItem ( 1, &tcItem );
	//VERIFY ( pPage1->Create ( CWikiBasePage2, &m_ctrTab ) );
	pPage2->SetWindowPos ( NULL, 10, 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	pPage2->ShowWindow ( SW_HIDE );*/

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
