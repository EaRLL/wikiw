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
	ON_BN_CLICKED ( IDC_PANEL_MAIN_GET1, OnGet1Click )
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

	b_Get1.Create ( L"Скоп.текст", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 310, 250, 410, 290 ), this, IDC_PANEL_MAIN_GET1 );
	b_Get1.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_Get1.SetFont ( &f_TitleButBig );

	l_cmndShrp.Create ( L"Текст", WS_CHILD | WS_VISIBLE, CRect ( 10, 10, 520, 55 ), this, IDC_PANEL_MAIN_LABEL ); //L"Текст\r\n123"
	l_cmndShrp.SetFont ( &f_TitleButBig );

	cMc_Line.Create ( WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, CRect ( 10, 60, 520, 240 ), this, 1552 );
	cMc_Line.SetFont ( &f_TitleButBig );


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

void CWikiBasePage1::OnGet1Click ( void )
{
	CString strData = L"";
	cMc_Line.GetWindowText ( strData );

	std::string s = CW2A ( strData.GetString ( ) );

	OpenClipboard ( );
	EmptyClipboard ( );
	HGLOBAL hg = GlobalAlloc ( GMEM_MOVEABLE, s.size ( ) + 1 );
	if ( !hg )
	{
		CloseClipboard ( );
		return;
	}
	memcpy ( GlobalLock ( hg ), s.c_str ( ), s.size ( ) + 1 );
	GlobalUnlock ( hg );
	SetClipboardData ( CF_TEXT, hg );
	CloseClipboard ( );
	GlobalFree ( hg );

}

UINT threadGet ( LPVOID Param )
{
	CString strData = _T ( "" );
	CString strData2 = _T ( "" );

	CString strUserAgent = _T ( "" );

	strUserAgent.Format ( _T ( "WikiW/%d.%d.%d.%d" ), APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_REVISION, APP_VERSION_BUILD );

	HINTERNET hInternet = InternetOpenA ( ( LPCSTR ) strUserAgent.GetBuffer ( strUserAgent.GetLength ( ) ), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );

	if ( !hInternet )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->l_cmndShrp.SetWindowText ( L"Connection Failed or Syntax error" );
		InternetCloseHandle ( hInternet );
		return 0;
	}

	HINTERNET hConnection = InternetConnectA ( hInternet, "ru.wikipedia.org", 80, "", "", INTERNET_SERVICE_HTTP, 0, 0 );

	if ( !hConnection )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->l_cmndShrp.SetWindowText ( L"Failed to open URL \nError No: " + ErrorNum );
		InternetCloseHandle ( hInternet );
		InternetCloseHandle ( hConnection );
		return 0;
	}

	//HINTERNET hData = HttpOpenRequestA ( hConnection, "GET", "/wiki/Чёрная дыра", NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0 );
	HINTERNET hData = HttpOpenRequestA ( hConnection, "GET", "/w/api.php?action=query&meta=siteinfo&siprop=namespaces&format=json", NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0 );

	if ( !hData )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->l_cmndShrp.SetWindowText ( L"Failed to open URL \nError No: " + ErrorNum );
		InternetCloseHandle ( hInternet );
		InternetCloseHandle ( hConnection );
		InternetCloseHandle ( hData );
		return 0;
	}

	HttpSendRequestA ( hData, NULL, 0, NULL, 0 );

	char DataReceived[ 12288 ];

	DWORD NumberOfBytesRead = 0;

	while ( InternetReadFile ( hData, DataReceived, sizeof( DataReceived ), &NumberOfBytesRead ) && NumberOfBytesRead )
	{
		strData2 = DataReceived;
		strData2 = strData2.Left ( NumberOfBytesRead );
		strData.Append ( strData2 );
	}
	
	//### { json
	std::string as = CW2A ( strData.GetString ( ) );
	const char* json = as.c_str ( );
	rapidjson::Document d;
	d.Parse ( json );

	// 2. Modify it by DOM.
	///rapidjson::Value& s = d[ "stars" ];
	///s.SetInt ( s.GetInt ( ) + 1 );

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer ( buffer );
	d.Accept ( writer );

	rapidjson::Value& s = d[ "query" ][ "namespaces" ][ "5" ][ "*" ];
	strData = s.GetString ( );

	//strData = buffer.GetString ( );
	//### } json

	//### { encoding
	std::string asa = CW2A ( strData.GetString ( ) );
	int wchars_num = MultiByteToWideChar ( CP_UTF8, 0, asa.c_str ( ), -1, NULL, 0 );
	wchar_t* wstr = new wchar_t[ wchars_num ];
	MultiByteToWideChar ( CP_UTF8, 0, asa.c_str ( ), -1, wstr, wchars_num );
	//### } encoding


	( ( CWikiBasePage1 * ) Param )->cMc_Line.SetWindowText ( wstr );

	InternetCloseHandle ( hInternet );
	InternetCloseHandle ( hConnection );
	InternetCloseHandle ( hData );

	( ( CWikiBasePage1 * ) Param )->l_cmndShrp.SetWindowText ( strUserAgent );
	( ( CWikiBasePage1 * ) Param )->cMc_Line.UpdateWindow ( );

	( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"End" );
	return 1;
}

void CWikiBasePage1::OnRefreshClick ( void )
{
	AfxBeginThread ( threadGet, this );
}
