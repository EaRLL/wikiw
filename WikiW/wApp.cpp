/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wApp.cpp
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

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
#pragma comment( compiler )

CWikiWApp::CWikiWApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CWikiWApp theApp;

BOOL CWikiWApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	EnableTaskbarInteraction(FALSE); ///
	SetRegistryKey(_T("WikiW"));
	pFrame = new CWikiBase;

	BOOL rc = pFrame->Create ( NULL, L"WikiW", WS_POPUP /* WS_OVERLAPPEDWINDOW*/, CRect ( 0, 0, 0, 0 ) );
	if ( !rc )
	{
		TRACE0 ( "\n Îøèáêà 1\n" );
		exit ( 1 );
	}

	CRect rcMonitor = xGetMonitorWorkArea ( pFrame );

	WindowWidth = so.APP_WIDTH;
	WindowHeight = so.APP_HEIGHT;
	WindowTop = ( int ) round ( ( rcMonitor.bottom - WindowHeight ) / 2 );
	WindowLeft = ( int ) round ( ( rcMonitor.right - WindowWidth ) / 2 );

	xCheckVersion ( );
	theApp.app_title = L"WikiW [" + so.m_wsVersion + L"]";

	pFrame->SetWindowPos ( NULL, WindowLeft, WindowTop, WindowWidth, WindowHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );

	CRect rcMonitorCheck;
	pFrame->GetClientRect ( &rcMonitorCheck );
	if ( rcMonitorCheck.right < WindowWidth )
		WindowWidth = WindowWidth + ( WindowWidth - rcMonitorCheck.right );
	if ( rcMonitorCheck.bottom < WindowHeight )
		WindowHeight = WindowHeight + ( WindowHeight - rcMonitorCheck.bottom );

	WindowTop = ( int ) round ( ( rcMonitor.bottom - WindowHeight ) / 2 );
	WindowLeft = ( int ) round ( ( rcMonitor.right - WindowWidth ) / 2 );

	pFrame->SetWindowPos ( NULL, WindowLeft, WindowTop, WindowWidth, WindowHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );
	pFrame->CreateChildControls ( );
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	m_pMainWnd = pFrame;
	return TRUE;
}

int CWikiWApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
