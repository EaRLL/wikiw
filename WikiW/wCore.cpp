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
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "stdafx.h"
#include "wCore.h"

xWOptions so;

void xCheckVersion ( )
{
	TCHAR szPath[ 260 ];
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

	so.m_wsVersion.Format ( _T ( "%i.%i.%i build %i" ), so.m_wnVersion[ 0 ], so.m_wnVersion[ 1 ], so.m_wnVersion[ 2 ], so.m_wnVersion[ 3 ] );
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