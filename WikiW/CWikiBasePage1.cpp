/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: CWikiBasePage1.cpp
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

BEGIN_MESSAGE_MAP ( CWikiBasePage1, CWnd )
	ON_WM_ERASEBKGND ( )
	ON_WM_NCHITTEST ( )
	//ON_WM_CTLCOLOR ( )
	ON_BN_CLICKED ( IDC_PANEL_MAIN_REFRESH, OnRefreshClick )
END_MESSAGE_MAP ( )

CWikiBasePage1::CWikiBasePage1 ( )
{
}

CWikiBasePage1::~CWikiBasePage1 ( )
{
}

BOOL CWikiBasePage1::OnEraseBkgnd ( CDC* pDC )
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

BOOL CWikiBasePage1::PreCreateWindow ( CREATESTRUCT& cs )
{
	if ( !CWnd::PreCreateWindow ( cs ) )
		return FALSE;
	cs.dwExStyle &= ~( WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU );
	cs.lpszClass = AfxRegisterWndClass ( CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor ( NULL, IDC_ARROW ), reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 ), NULL );

	return TRUE;
}

void CWikiBasePage1::CreateChildControls ( void )
{
	xCreateFastFont ( f_TitleButBig, 14, 600, _T ( "Tahoma" ) );

	b_Refresh.Create ( L"Обновить", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 420, 250, 520, 290 ), this, IDC_PANEL_MAIN_REFRESH );
	b_Refresh.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBGrayColors );
	b_Refresh.SetFont ( &f_TitleButBig );
	//this->EnableWindow(0);

	l_cmndShrp.Create ( L"Текст", WS_CHILD | WS_VISIBLE, CRect ( 10, 10, 520, 120 ), this, IDC_PANEL_MAIN_LABEL ); //L"Текст\r\n123"
	l_cmndShrp.SetFont ( &f_TitleButBig );


}

/*HBRUSH CWikiBasePage1::OnCtlColor ( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	UINT id = pWnd->GetDlgCtrlID ( );
	if ( id == IDC_PANEL_MAIN_LABEL )
	{
		pDC->SetTextColor ( so.APP_COLOR_TEXT );
		pDC->SetBkColor ( so.APP_COLOR_TEXT_BG );
		return ( HBRUSH )::GetStockObject ( NULL_BRUSH );
	}
	else
	{
		return ( HBRUSH )::GetStockObject ( NULL_BRUSH );
	}
}*/

void CWikiBasePage1::OnRefreshClick ( void )
{
	CString strData = _T ( "" );

	CInternetSession mySession;

	CHttpFile *pHttpFile;
	char inBuf[ 10000 ];
	UINT nBytesRead;

	try
	{
		// Open HTTP file
		pHttpFile = ( CHttpFile * ) mySession.OpenURL ( L"http://google.com/" );
	}
	catch ( CInternetException )
	{
		l_cmndShrp.SetWindowText ( L"Received Exception from OpenURL()" );
		l_cmndShrp.UpdateWindow ( );
	}

	if ( pHttpFile == NULL )
	{
		l_cmndShrp.SetWindowText ( L"Error in OpenURL" );
		l_cmndShrp.UpdateWindow ( );
	}
	else
	{
		// Read from file
		nBytesRead = pHttpFile->Read ( inBuf, sizeof( inBuf ) );
		strData.Format ( L"Read %d bytes", nBytesRead );
		l_cmndShrp.SetWindowText ( strData );
		l_cmndShrp.UpdateWindow ( );
	}

	b_Refresh.SetWindowText ( theApp.app_title );
}
