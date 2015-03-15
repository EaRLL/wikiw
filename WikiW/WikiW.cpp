#include "stdafx.h"
#include "WikiW.h"

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
	pFrame = new CMainFrame;
	//if (!pFrame)
	//	return FALSE;

	BOOL rc = pFrame->Create ( NULL, L"text", WS_OVERLAPPEDWINDOW, CRect ( 0, 0, 0, 0 ) );
	if ( !rc )
	{
		TRACE0 ( "\n Îøèáêà 1\n" );
		exit ( 1 );
	}

	pFrame->SetWindowPos ( NULL, 100, 100, 300, 300, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING );
	//pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	m_pMainWnd = pFrame;
	return TRUE;
}

int CWikiWApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
