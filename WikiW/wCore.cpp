/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wCore.cpp
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
#include "wCore.h"

xWOptions so;

void xCheckVersion ( )
{
	/*TCHAR szPath[ 260 ];
	DWORD dwSize = 0;

	so.m_wnVersion[ 0 ] = so.m_wnVersion[ 1 ] = so.m_wnVersion[ 2 ] = so.m_wnVersion[ 3 ] = 0;

	if ( GetModuleFileName ( NULL, szPath, 260 ) )
	{
		so.m_wsPath = szPath;
		dwSize = GetFileVersionInfoSize ( szPath, &dwSize );
	}

	if ( dwSize > 0 )
	{
		BYTE* pBuffer = new BYTE[ dwSize ];

		if ( GetFileVersionInfo ( szPath, NULL, dwSize, pBuffer ) )
		{
			VS_FIXEDFILEINFO* pTable;

			if ( VerQueryValue ( pBuffer, _T ( "\\" ), ( VOID** ) &pTable, ( UINT* ) &dwSize ) )
			{
				so.m_wnVersion[ 0 ] = ( WORD ) ( pTable->dwFileVersionMS >> 16 );
				so.m_wnVersion[ 1 ] = ( WORD ) ( pTable->dwFileVersionMS & 0xFFFF );
				so.m_wnVersion[ 2 ] = ( WORD ) ( pTable->dwFileVersionLS >> 16 );
				so.m_wnVersion[ 3 ] = ( WORD ) ( pTable->dwFileVersionLS & 0xFFFF );
			}
		}

		delete[ ] pBuffer;
	}
	*/
	//so.m_wsVersion.Format ( _T ( "%i.%i.%i build %i" ), so.m_wnVersion[ 0 ], so.m_wnVersion[ 1 ], so.m_wnVersion[ 2 ], so.m_wnVersion[ 3 ] );
	so.m_wsVersion = APP_VERSION_FILE_STR;
}

void xCreateFastFont ( CFont& pFont, INT nHeight, INT nWeight, CString nFontName )
{
	VERIFY ( pFont.CreateFont (
		nHeight,                   // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		nWeight,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		CLEARTYPE_QUALITY,         // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		nFontName )
		);
}

void xInitFont ( CString nFontName )
{
	AddFontResourceEx ( nFontName, FR_PRIVATE, NULL );
}

CString xGetTime ( )
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[ 80 ];
	CString resultSr;

	time ( &rawtime );
	localtime_s ( &timeinfo, &rawtime );

	strftime ( buffer, 80, "Сейчас %Y, %A, %B %d, %X", &timeinfo );

	resultSr = buffer;

	return resultSr;
}

UINT xParseWikiApiThread ( LPVOID Param )
{
	CString strData = _T ( "" );
	CString strData2 = _T ( "" );
	CString strUserAgent = _T ( "" );

	( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"Соединение..." );

	strUserAgent.Format ( _T ( "WikiW/%d.%d.%d.%d" ), APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_REVISION, APP_VERSION_BUILD );

	HINTERNET hInternet = InternetOpenA ( ( LPCSTR ) strUserAgent.GetBuffer ( strUserAgent.GetLength ( ) ), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );

	if ( !hInternet )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"Соединение прервано" );
		InternetCloseHandle ( hInternet );
		return 0;
	}

	HINTERNET hConnection = InternetConnectA ( hInternet, "ru.wikipedia.org", 80, "", "", INTERNET_SERVICE_HTTP, 0, 0 );

	if ( !hConnection )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"Ошибка#1" + ErrorNum );
		InternetCloseHandle ( hInternet );
		InternetCloseHandle ( hConnection );
		return 0;
	}

	HINTERNET hData = HttpOpenRequestA ( hConnection, "GET", ( ( CWikiBasePage1 * ) Param )->api_url, NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0 );

	if ( !hData )
	{
		DWORD ErrorNum = GetLastError ( );
		( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"Ошибка#2" + ErrorNum );
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
	( ( CWikiBasePage1 * ) Param )->cMc_Line.UpdateWindow ( );

	InternetCloseHandle ( hInternet );
	InternetCloseHandle ( hConnection );
	InternetCloseHandle ( hData );

	( ( CWikiBasePage1 * ) Param )->b_Refresh.SetWindowText ( L"Данные обновлены" );
	( ( CWikiBasePage1 * ) Param )->isConnected = false;
	return 1;
}

CString xParseWikiApi ( LPVOID lParam )
{
	AfxBeginThread ( xParseWikiApiThread, lParam );
	return L"";
}

// MonitorAPI
struct MonitorAPI
{
	MonitorAPI ( );
	~MonitorAPI ( );

	struct MonitorInfo
	{
		MonitorInfo ( ) : cbSize ( sizeof( MonitorInfo ) )
		{
		}

		DWORD cbSize;
		RECT rcMonitor;
		RECT rcWork;
		DWORD dwFlags;
	};

	enum
	{
		DefaultToNull = 0,
		DefaultToPrimary = 1,
		DefaultToNearest = 2
	};

	typedef HANDLE ( WINAPI* pfnMonitorFromPoint )( POINT pt, DWORD dwFlags );
	typedef BOOL ( WINAPI* pfnGetMonitorInfo )( HANDLE hMonitor, MonitorInfo* pmi );
	typedef HANDLE ( WINAPI* pfnMonitorFromWindow )( HWND hWnd, DWORD dwFlags );

	pfnMonitorFromPoint pMonitorFromPoint;
	pfnMonitorFromWindow pMonitorFromWindow;
	pfnGetMonitorInfo pGetMonitorInfo;

	bool IsLoaded ( ) const
	{
		return hUser32 != NULL;
	}

	HINSTANCE hUser32;
};

static MonitorAPI theMonitorAPI;

MonitorAPI::MonitorAPI ( )
: pMonitorFromPoint ( NULL ),
pMonitorFromWindow ( NULL ),
pGetMonitorInfo ( NULL )
{
	hUser32 = ::LoadLibrary ( _T ( "user32.dll" ) );
	if ( hUser32 != NULL )
	{
		pMonitorFromPoint = ( pfnMonitorFromPoint ) ::GetProcAddress ( hUser32, "MonitorFromPoint" );
		pMonitorFromWindow = ( pfnMonitorFromWindow ) ::GetProcAddress ( hUser32, "MonitorFromWindow" );
		pGetMonitorInfo = ( pfnGetMonitorInfo ) ::GetProcAddress ( hUser32, "GetMonitorInfoA" );

		if ( pMonitorFromPoint == NULL
			 || pMonitorFromWindow == NULL
			 || pGetMonitorInfo == NULL )
		{
			::FreeLibrary ( hUser32 );
			hUser32 = NULL;
		}
	}
}

MonitorAPI::~MonitorAPI ( )
{
	if ( hUser32 != NULL )
		::FreeLibrary ( hUser32 );
}

CRect xGetMonitorWorkArea ( const CPoint& point )
{
	CRect rcWorkArea;

	if ( !::SystemParametersInfo ( SPI_GETWORKAREA, 0, ( PVOID ) &rcWorkArea, false ) )
	{
		CSize szScreen ( ::GetSystemMetrics ( SM_CXSCREEN ), ::GetSystemMetrics ( SM_CYSCREEN ) );
		rcWorkArea = CRect ( CPoint ( 0, 0 ), szScreen );
	}

	if ( theMonitorAPI.IsLoaded ( ) )
	{
		MonitorAPI::MonitorInfo mi;
		HANDLE hMonitor = theMonitorAPI.pMonitorFromPoint ( point, MonitorAPI::DefaultToNearest );
		if ( hMonitor != NULL && theMonitorAPI.pGetMonitorInfo ( hMonitor, &mi ) )
			rcWorkArea = mi.rcWork;
	}

	return rcWorkArea;
}

CRect xGetMonitorWorkArea ( CWnd* pWnd )
{
	CRect rcWorkArea;

	if ( !::SystemParametersInfo ( SPI_GETWORKAREA, 0, ( PVOID ) &rcWorkArea, false ) )
	{
		CSize szScreen ( ::GetSystemMetrics ( SM_CXSCREEN ), ::GetSystemMetrics ( SM_CYSCREEN ) );
		rcWorkArea = CRect ( CPoint ( 0, 0 ), szScreen );
	}

	if ( theMonitorAPI.IsLoaded ( ) )
	{
		MonitorAPI::MonitorInfo mi;
		HANDLE hMonitor = theMonitorAPI.pMonitorFromWindow ( pWnd->GetSafeHwnd ( ), MonitorAPI::DefaultToNearest );
		if ( hMonitor != NULL && theMonitorAPI.pGetMonitorInfo ( hMonitor, &mi ) )
			rcWorkArea = mi.rcWork;
	}

	return rcWorkArea;
}

CRect xGetMonitorRect ( CWnd* pWnd )
{
	CSize szScreen ( ::GetSystemMetrics ( SM_CXSCREEN ), ::GetSystemMetrics ( SM_CYSCREEN ) );
	CRect rcMonitor ( CPoint ( 0, 0 ), szScreen );

	if ( theMonitorAPI.IsLoaded ( ) )
	{
		MonitorAPI::MonitorInfo mi;
		HANDLE hMonitor = theMonitorAPI.pMonitorFromWindow ( pWnd->GetSafeHwnd ( ), MonitorAPI::DefaultToNearest );
		if ( hMonitor != NULL && theMonitorAPI.pGetMonitorInfo ( hMonitor, &mi ) )
			rcMonitor = mi.rcMonitor;
	}

	return rcMonitor;
}
