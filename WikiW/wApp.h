/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: wApp.h
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
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "wCore.h"
#include "wBase.h"

class CWikiWApp : public CWinApp
{
public:
	CWikiWApp ( );
	virtual BOOL InitInstance ( void );
	virtual int ExitInstance ( );
	CWikiBase* pFrame;
	int WindowTop;
	int WindowLeft;
	int WindowWidth;
	int WindowHeight;
	CString app_title;
};

extern CWikiWApp theApp;
