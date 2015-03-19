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
	cs.dwExStyle &= ~( WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU );
	cs.lpszClass = AfxRegisterWndClass ( CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor ( NULL, IDC_ARROW ), reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 ), NULL );

	return TRUE;
}
void CWikiBasePage1::CreateChildControls ( void )
{
	xCreateFastFont ( f_TitleButBig, 20, 600, _T ( "Verdana" ) );

	b_Options.Create ( L"Настройки", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, CRect ( 10, 10, 200, 60 ), this, IDC_TIMEBTN1 );
	b_Options.b_Colors = reinterpret_cast<CFlatButton::sColors*>( &so.FlatBMainColors );
	b_Options.SetFont ( &f_TitleButBig );
}
