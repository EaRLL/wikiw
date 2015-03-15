#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"
#include "MainFrm.h"

class CWikiWApp : public CWinApp
{
public:
	CWikiWApp ( );
	virtual BOOL InitInstance ( void );
	virtual int ExitInstance ( );
	CMainFrame* pFrame;
};

extern CWikiWApp theApp;
